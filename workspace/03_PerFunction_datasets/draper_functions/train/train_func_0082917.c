ipx_getnode(u_int8_t *node, const char *str)
{
	int i;
	u_int32_t tmp;

	for(i = 0; i < 6; i++) {
		if ((tmp = hexget(*str++)) & 0xf0)
			return -1;
		node[i] = (u_int8_t)tmp;
		node[i] <<= 4;
		if ((tmp = hexget(*str++)) & 0xf0)
			return -1;
		node[i] |= (u_int8_t)tmp;
		if (*str == ':')
			str++;
	}

	return 0;
}
