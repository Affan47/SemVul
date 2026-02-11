val2str(uint16_t val, const struct valstr *vs)
{
	static char un_str[32];
	int i;

	for (i = 0; vs[i].str != NULL; i++) {
		if (vs[i].val == val)
			return vs[i].str;
	}

	memset(un_str, 0, 32);
	snprintf(un_str, 32, "Unknown (0x%02X)", val);

	return un_str;
}
