chcopy(char* p, char* q)
{
	int c;

	while(c = *q) {
		if(c == '"')
			*p++ = '\\';
		*p++ = c;
		q++;
	}
	*p = 0;
	return p;
}
