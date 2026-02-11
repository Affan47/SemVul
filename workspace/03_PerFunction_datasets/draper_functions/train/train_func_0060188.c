gs_c_rtrim(char *str, const char *reject)
{
	char *s=gs_r_reject(str,reject);
	if(!s) {
		*str=0;
		return str;
	}
	s[1]=0;
	return str;
}
