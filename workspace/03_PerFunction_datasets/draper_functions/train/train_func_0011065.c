GF_IPMPX_ParseBinData(char *val, char **out_data, u32 *out_data_size)
{
	u32 i, c, len;
	char s[3];

	if (val[0] != '%') {
		len = *out_data_size = strlen(val);
		*out_data = (char*)gf_malloc(sizeof(char) * len);
		memcpy(*out_data, val, sizeof(char) * len);
		return;
	}

	len = strlen(val) / 3;
	if (*out_data) gf_free(*out_data);
	*out_data_size = len;
	*out_data = (char*)gf_malloc(sizeof(char) * len);
	s[2] = 0;
	for (i=0; i<len; i++) {
		s[0] = val[3*i+1];
		s[1] = val[3*i+2];
		sscanf(s, "%02X", &c);
		(*out_data)[i] = (unsigned char) c;
	}
}
