str2facility(char *s)
{
	int i;

	for( i=0; str_fac[i] ; i++) {
		if (!strcasecmp(s,str_fac[i]))
			return int_fac[i];
	}
	return -1;
}
