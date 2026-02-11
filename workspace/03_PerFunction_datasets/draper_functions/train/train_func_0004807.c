dst_key_to_buffer(DST_KEY *key, u_char *out_buff, unsigned buf_len)
{
	int len;

	if(key == NULL)
		return (0);
	if(key->dk_func != NULL && key->dk_func != NULL) {
		len = key->dk_func->to_dns_key(key, out_buff, buf_len);
		if (len < 0)
			return (0);
		return (len);
	}
	return (0);
}
