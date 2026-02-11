dbg_is_all_ff(uint8_t *buf, int len)
{
	int i;

	for (i = 0; i < len; i++)
		if (buf[i] != 0xff)
			return 0;
	return 1;
}
