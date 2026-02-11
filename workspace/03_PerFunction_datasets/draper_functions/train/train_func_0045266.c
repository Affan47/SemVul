string_remove_trailing_slashes(char *str)
{
	char *s = str;


	while(*s)
		s++;
	s--;


	while(s > str && *s == '/') {
		*s = 0;
		s--;
	}
}
