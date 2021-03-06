/*
 *  Copyright (C) 2010, Imagis Technology Co. Ltd. All Rights Reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 */

#ifndef __IST30XX_CMCS_H__
#define __IST30XX_CMCS_H__

#define IST30XX_INTERNAL_CMCS_BIN   (1)

#define CMCS_FLAG_CM                (1)
#define CMCS_FLAG_CM_SPEC           (1 << 1)
#define CMCS_FLAG_CM_SLOPE0         (1 << 2)
#define CMCS_FLAG_CM_SLOPE1         (1 << 3)
#define CMCS_FLAG_CS0               (1 << 4)
#define CMCS_FLAG_CS1               (1 << 5)

#define FLAG_ENABLE_CM              (1)
#define FLAG_ENABLE_CS              (2)
#define FLAG_ENABLE_CR              (4)

#define CMCS_READY                  (0)
#define CMCS_NOT_READY              (-1)

#define CMCS_PARSING_DEBUG          (0)
#define CMCS_RAMCODE_READ           (0)

#define IST30XX_CMCS_MSG_VALID      (0x8FAB0FAB)

// CMCS addr
#define IST30XX_CMCS_CHECKSUM       IST30XX_DA_ADDR(0x300B0100)
#define IST30XX_CMCS_PATTERN        IST30XX_DA_ADDR(0x300B0104)
#define IST30XX_CMCS_RESULT         IST30XX_DA_ADDR(0x00001180)
#if (IMAGIS_TSP_IC < IMAGIS_IST3038C)
#define IST30XX_CMCS_RESULT_SIZE    0x200
#else
#define IST30XX_CMCS_RESULT_SIZE    0x480
#endif

#define ENABLE_CM_MODE(n)           (n & 1)
#define ENABLE_CS_MODE(n)           ((n >> 1) & 1)

#define IST30XX_CMCS_NAME           "ist30xxc.cms"
#define IST30XX_CMCS_MAGIC          "CMCS2TAG"
struct CMCS_ADDR_INFO {
	u32	base_screen;
	u32	base_key;
	u32	start_cp;
	u32	vcmp;
	u32	sensor1;
	u32	sensor2;
	u32	sensor3;
    u32 cmcs_size;
};
struct CMCS_CH_NUM {
	u8	tx;
	u8	rx;
};
struct CMCS_CH_INFO {
	u8	tx_num;
	u8	rx_num;
	u8	scr_tx_num;
    u8	scr_rx_num;
    u8	gtx_use_num;
	u8	gtx_ch_num[4];
	u8	key_use_num;
	struct CMCS_CH_NUM key_ch_num[5];
};
struct CMCS_SLOPE_INFO {
	s16	x_min;
	s16	x_max;
	s16	y_min;
	s16	y_max;
	s16	gtx_x_min;
	s16	gtx_x_max;
	s16	gtx_y_min;
	s16	gtx_y_max;    
	s16	key_min;
	s16	key_max;
};
struct CMCS_SPEC_INFO {
	u16	screen_min;
	u16	screen_max;
	u16	gtx_min;
	u16	gtx_max;
	u16	key_min;
	u16	key_max;
};
struct CMCS_CMD {
	u16	mode;   // enable bit
	u16	cmcs_size;
	u16	base_screen;
	u16	base_key;
	u8	start_cp_cm;
	u8	start_cp_cs;
	u8	vcmp_cm;
	u8	vcmp_cs;
	u32	reserved; // for checksum of firmware
};
typedef struct _CMCS_INFO {
	u32			timeout;
	struct CMCS_ADDR_INFO	addr;
	struct CMCS_CH_INFO 	ch;
	struct CMCS_SPEC_INFO	spec_cr;
	struct CMCS_SPEC_INFO	spec_cs0;
	struct CMCS_SPEC_INFO	spec_cs1;
	struct CMCS_SLOPE_INFO	slope;
    u16			sensor1_size;
	u16			sensor2_size;
	u16			sensor3_size;
	u16			reserved;
	u32			cmcs_chksum;
	u32			sensor_chksum;
	struct CMCS_CMD		cmd;
} CMCS_INFO;

typedef struct _CMCS_BIN_INFO {
	char		magic1[8];
	CMCS_INFO	cmcs;
	u8 *		buf_cmcs;
	u32 *		buf_sensor;
   	u16 *		buf_cm_min;
    u16 *		buf_cm_max;
	char		magic2[8];
} CMCS_BIN_INFO;

typedef struct _CMCS_BUF {
	s16	cm[IST30XX_NODE_TOTAL_NUM];
	s16	cm_spec_min[IST30XX_NODE_TOTAL_NUM];
    s16 cm_spec_max[IST30XX_NODE_TOTAL_NUM];
	s16	slope0[IST30XX_NODE_TOTAL_NUM];
	s16	slope1[IST30XX_NODE_TOTAL_NUM];
	s16	cs0[IST30XX_NODE_TOTAL_NUM];
	s16	cs1[IST30XX_NODE_TOTAL_NUM];
} CMCS_BUF;

int check_tsp_type(int tx, int rx);
int ist30xx_get_cmcs_info(const u8 *buf, const u32 size);
int ist30xx_cmcs_test(struct ist30xx_data *data, const u8 *buf, int size);
int ist30xx_init_cmcs_sysfs(struct ist30xx_data *data);

#endif  // __IST30XX_CMCS_H__
