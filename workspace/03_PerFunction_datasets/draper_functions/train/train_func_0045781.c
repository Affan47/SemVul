byteaout(PG_FUNCTION_ARGS)
{
	bytea	   *vlena = PG_GETARG_BYTEA_P(0);
	char	   *result;
	char	   *vp;
	char	   *rp;
	int			val;
	int			i;
	int			len;

	len = 1;
	vp = VARDATA(vlena);
	for (i = VARSIZE(vlena) - VARHDRSZ; i != 0; i--, vp++)
	{
		if (*vp == '\\')
			len += 2;
		else if ((unsigned char) *vp < 0x20 || (unsigned char) *vp > 0x7e)
			len += 4;
		else
			len++;
	}
	rp = result = (char *) palloc(len);
	vp = VARDATA(vlena);
	for (i = VARSIZE(vlena) - VARHDRSZ; i != 0; i--, vp++)
	{
		if (*vp == '\\')
		{
			*rp++ = '\\';
			*rp++ = '\\';
		}
		else if ((unsigned char) *vp < 0x20 || (unsigned char) *vp > 0x7e)
		{
			val = *vp;
			rp[0] = '\\';
			rp[3] = DIG(val & 07);
			val >>= 3;
			rp[2] = DIG(val & 07);
			val >>= 3;
			rp[1] = DIG(val & 03);
			rp += 4;
		}
		else
			*rp++ = *vp;
	}
	*rp = '\0';
	PG_RETURN_CSTRING(result);
}
