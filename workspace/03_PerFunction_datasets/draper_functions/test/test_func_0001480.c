encode_ie(char *in, u8 *out, int maxlen)
{
	int l = 0;
	while (*in) {
		if (!isxdigit(in[0]) || !isxdigit(in[1]) || l >= maxlen)
			return -1;
		out[++l] = (hex_to_bin(in[0]) << 4) + hex_to_bin(in[1]);
		in += 2;
	}
	out[0] = l;
	return l;
}
