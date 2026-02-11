utf_char2bytes(c, buf)
    int		c;
    char_u	*buf;
{
    if (c < 0x80)
    {
	buf[0] = c;
	return 1;
    }
    if (c < 0x800)
    {
	buf[0] = 0xc0 + ((unsigned)c >> 6);
	buf[1] = 0x80 + (c & 0x3f);
	return 2;
    }
    if (c < 0x10000)
    {
	buf[0] = 0xe0 + ((unsigned)c >> 12);
	buf[1] = 0x80 + (((unsigned)c >> 6) & 0x3f);
	buf[2] = 0x80 + (c & 0x3f);
	return 3;
    }
    if (c < 0x200000)
    {
	buf[0] = 0xf0 + ((unsigned)c >> 18);
	buf[1] = 0x80 + (((unsigned)c >> 12) & 0x3f);
	buf[2] = 0x80 + (((unsigned)c >> 6) & 0x3f);
	buf[3] = 0x80 + (c & 0x3f);
	return 4;
    }
    if (c < 0x4000000)
    {
	buf[0] = 0xf8 + ((unsigned)c >> 24);
	buf[1] = 0x80 + (((unsigned)c >> 18) & 0x3f);
	buf[2] = 0x80 + (((unsigned)c >> 12) & 0x3f);
	buf[3] = 0x80 + (((unsigned)c >> 6) & 0x3f);
	buf[4] = 0x80 + (c & 0x3f);
	return 5;
    }

    buf[0] = 0xfc + ((unsigned)c >> 30);
    buf[1] = 0x80 + (((unsigned)c >> 24) & 0x3f);
    buf[2] = 0x80 + (((unsigned)c >> 18) & 0x3f);
    buf[3] = 0x80 + (((unsigned)c >> 12) & 0x3f);
    buf[4] = 0x80 + (((unsigned)c >> 6) & 0x3f);
    buf[5] = 0x80 + (c & 0x3f);
    return 6;
}
