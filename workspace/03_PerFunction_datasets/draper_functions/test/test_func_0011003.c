gs_last_indexof(const char *string, const char *rech, int (*isaffix)(const char *, const char *))
{
	const char *s = string+strlen(string)-strlen(rech);
	if(!isaffix) isaffix=gs_is_affix;

	while(s>=string) {
		if((*isaffix)(s,rech)) return (char *)s;
		s--;
	}
	return NULL;
}
