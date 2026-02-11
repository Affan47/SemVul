utils_bin2hexstr (const char *bytes, int len, int final_len)
{
	static char hex_digits[] = "0123456789abcdef";
	char *result;
	int i;
	gsize buflen = (len * 2) + 1;

	g_return_val_if_fail (bytes != NULL, NULL);
	g_return_val_if_fail (len > 0, NULL);
	g_return_val_if_fail (len < 4096, NULL);
	if (final_len > -1)
		g_return_val_if_fail (final_len < buflen, NULL);

	result = g_malloc0 (buflen);
	for (i = 0; i < len; i++)
	{
		result[2*i] = hex_digits[(bytes[i] >> 4) & 0xf];
		result[2*i+1] = hex_digits[bytes[i] & 0xf];
	}

	if (final_len > -1)
		result[final_len] = '\0';
	else
		result[buflen - 1] = '\0';

	return result;
}
