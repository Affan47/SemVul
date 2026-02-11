check_strcncpy(char* dst, char* src, char delim, int maxlength)
{
	char* p = dst;
	while(*src && *src != delim)
	{
		*p++ = *src++;
		if(p - dst > maxlength)
			error_exit("Field too long");
	}
	*p = 0;
	return p - dst;
}
