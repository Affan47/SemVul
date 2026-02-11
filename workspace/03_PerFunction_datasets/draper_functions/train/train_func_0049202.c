ncx_getn_schar_float(const void **xpp, size_t nelems, float *tp)
{
	schar *xp = (schar *)(*xpp);

	while(nelems-- != 0)
	{
		*tp++ = *xp++;
	}

	*xpp = (const void *)xp;
	return ENOERR;
}
