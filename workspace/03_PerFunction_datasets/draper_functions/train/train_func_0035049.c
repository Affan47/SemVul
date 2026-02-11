raw_send_data_frame(lcm_cmd_t cmd, const char *data, const unsigned int len)
{
    unsigned int di;
    unsigned int fi;
    static char frame[32];
    u_int16_t crc = 0;

    frame[0] = LCM_FRAME_MASK;

    frame[1] = cmd;
    crc = CRC16(frame[1], crc);

    frame[2] = HI8(len);
    crc = CRC16(frame[2], crc);

    frame[3] = LO8(len);
    crc = CRC16(frame[3], crc);

#define APPEND(value)				       \
    do {					       \
	const unsigned char v = (value);	       \
	if ((v == LCM_FRAME_MASK) || (v == LCM_ESC)) { \
	    frame[fi++] = LCM_ESC;		       \
	}					       \
	frame[fi++] = v;			       \
	crc = CRC16(v, crc);			       \
    } while (0)

#define APPEND_NOCRC(value)			       \
    do {					       \
	const unsigned char v = (value);	       \
	if ((v == LCM_FRAME_MASK) || (v == LCM_ESC)) { \
	    frame[fi++] = LCM_ESC;		       \
	}					       \
	frame[fi++] = v;			       \
    } while (0)

    for (fi = 4, di = 0; di < len; di++) {
	APPEND(data[di]);
    }

    APPEND_NOCRC(HI8(crc));
    APPEND_NOCRC(LO8(crc));

    frame[fi++] = LCM_FRAME_MASK;

    debug_data(" TXD ", frame, fi);
    drv_generic_serial_write(frame, fi);

#undef APPEND

    usleep(500);
}
