hexbyte(const char *p)
{
    if (!is_hex(p[0]) || !is_hex(p[1]))
	return -1;
    else
	return (hexval(p[0]) << 4) + hexval(p[1]);
}
