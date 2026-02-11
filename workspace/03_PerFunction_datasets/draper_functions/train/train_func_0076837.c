str2lower(char *str, int len)
{
	char *res = (char *)malloc(len+1);
	char *p;

	for(p=res; p<res+len; p++, str++) {
		*p = tolower(*str);
	}

	*p = 0;

	return res;
}
