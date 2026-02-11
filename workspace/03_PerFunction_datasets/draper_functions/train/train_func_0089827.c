drac3Crc16(const char *str,
	const int l) {

    int i,j;
    guint16 crc = 0;

    for (i=0; i<l; i++) {
        crc = crc ^ (str[i] << 8);
        for (j=0; j<8; j++)
            crc = ( (crc & 0x8000) == 32768 ? (crc<<1) ^ 0x1021 : crc<<1);
    }
    crc = crc & 0xFFFF;
    return crc;
}
