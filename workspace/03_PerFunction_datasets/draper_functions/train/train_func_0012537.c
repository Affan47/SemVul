gs_nstr(const char *str, const char *rech)
{
	const char *s=str;
	size_t n=0;
	size_t len_rech = strlen(rech);

	while(s) {
		s=strstr(s,rech);
		if(s) {
			n++; s+=len_rech;
		}
	}

	return n;
}
