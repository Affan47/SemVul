mic2euc_jp(const unsigned char *mic, unsigned char *p, int len)
{
	int			c1;
	int			l;

	while (len > 0)
	{
		c1 = *mic;
		if (!IS_HIGHBIT_SET(c1))
		{

			if (c1 == 0)
				report_invalid_encoding(PG_MULE_INTERNAL,
										(const char *) mic, len);
			*p++ = c1;
			mic++;
			len--;
			continue;
		}
		l = pg_encoding_verifymb(PG_MULE_INTERNAL, (const char *) mic, len);
		if (l < 0)
			report_invalid_encoding(PG_MULE_INTERNAL,
									(const char *) mic, len);
		if (c1 == LC_JISX0201K)
		{
			*p++ = SS2;
			*p++ = mic[1];
		}
		else if (c1 == LC_JISX0212)
		{
			*p++ = SS3;
			*p++ = mic[1];
			*p++ = mic[2];
		}
		else if (c1 == LC_JISX0208)
		{
			*p++ = mic[1];
			*p++ = mic[2];
		}
		else
			report_untranslatable_char(PG_MULE_INTERNAL, PG_EUC_JP,
									   (const char *) mic, len);
		mic += l;
		len -= l;
	}
	*p = '\0';
}
