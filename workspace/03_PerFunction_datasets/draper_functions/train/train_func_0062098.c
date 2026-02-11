png_crc(const char *buf, size_t len)
{
    unsigned long c = 0xffffffffL;
    int n;

    for (n = 0; n < len; n++)
	c = png_crc_table[(c ^ *((unsigned char *)buf + n)) & 0xff] ^ (c >> 8);
    return c ^ 0xffffffffL;
}
