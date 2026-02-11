string_trim(char *s, int func(int))
{
	char *p;


	while (func(*s))
		s++;


	p = s + strlen(s) - 1;
	while (func(*p))
		p--;


	*(p + 1) = 0;

	return s;
}
