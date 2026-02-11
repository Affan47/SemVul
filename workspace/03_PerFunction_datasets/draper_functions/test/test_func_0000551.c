crypt_encode(from, len, to)
    char_u	*from;
    size_t	len;
    char_u	*to;
{
    size_t	i;
    int		ztemp, t;

    if (use_crypt_method == 0)
	for (i = 0; i < len; ++i)
	{
	    ztemp = from[i];
	    DECRYPT_BYTE_ZIP(t);
	    UPDATE_KEYS_ZIP(ztemp);
	    to[i] = t ^ ztemp;
	}
    else
	bf_crypt_encode(from, len, to);
}
