EC_POINT_point2hex(const EC_GROUP *group,
                         const EC_POINT *point,
                         point_conversion_form_t form,
                         BN_CTX *ctx)
	{
	char          *ret, *p;
	size_t        buf_len=0,i;
	unsigned char *buf, *pbuf;

	buf_len = EC_POINT_point2oct(group, point, form,
                                     NULL, 0, ctx);
	if (buf_len == 0)
		return NULL;

	if ((buf = OPENSSL_malloc(buf_len)) == NULL)
		return NULL;

	if (!EC_POINT_point2oct(group, point, form, buf, buf_len, ctx))
		{
		OPENSSL_free(buf);
		return NULL;
		}

	ret = (char *)OPENSSL_malloc(buf_len*2+2);
	if (ret == NULL)
		{
		OPENSSL_free(buf);
		return NULL;
		}
	p = ret;
	pbuf = buf;
	for (i=buf_len; i > 0; i--)
		{
			int v = (int) *(pbuf++);
			*(p++)=HEX_DIGITS[v>>4];
			*(p++)=HEX_DIGITS[v&0x0F];
		}
	*p='\0';

	OPENSSL_free(buf);

	return ret;
	}
