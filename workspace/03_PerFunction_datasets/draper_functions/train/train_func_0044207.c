update_crc(guint32 crc, const guchar *buf, guint len) {
    guint32 c = crc;
    guint n;

    if (!crc_table_computed)
	make_crc_table();
    for (n = 0; n < len; n++) {
	c = crc_table[(c ^ buf[n]) & 0xff] ^ (c >> 8);
    }
    return c;
}
