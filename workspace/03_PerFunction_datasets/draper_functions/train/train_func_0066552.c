hex2byte(char *hex)
{
	int d1, d2;

	d1 = hex2num(hex[0]);
	if (d1 < 0)
		return -1;
	d2 = hex2num(hex[1]);
	if (d2 < 0)
		return -1;
	return (d1 << 4) | d2;
}
