php_strtr_hash(const char *str, int len)
{
	HASH	res = 0;
	int		i;
	for (i = 0; i < len; i++) {
		res = res * 33 + (unsigned char)str[i];
	}

	return res;
}
