_make_printable(const unsigned char *str, int size)
{
	unsigned char *buf;
	int n, i;
	jdns_string_t *out;

	if(size == 0)
	{
		out = jdns_string_new();
		jdns_string_set_cstr(out, "");
		return out;
	}


	buf = (unsigned char *)malloc(size * 4);
	i = 0;
	for(n = 0; n < size; ++n)
	{
		unsigned char c = str[n];
		if(c == '\\')
		{
			buf[i++] = '\\';
			buf[i++] = '\\';
		}
		else if(c >= 0x20 && c < 0x7f)
		{
			buf[i++] = c;
		}
		else
		{
			buf[i++] = '\\';
			buf[i++] = 'x';
			_hex_byte(c, buf + i);
			i += 2;
		}
	}

	out = jdns_string_new();
	jdns_string_set(out, buf, i);
	free(buf);
	return out;
}
