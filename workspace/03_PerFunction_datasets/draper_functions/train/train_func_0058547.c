string_pad_right(char *old, unsigned int length)
{
	unsigned int i;
	char *s = malloc(length + 1);
	if(!s)
		return 0;

	if(strlen(old) <= length) {
		strcpy(s, old);
		for(i = strlen(old); i < length; i++) {
			s[i] = ' ';
		}
	} else {
		strncpy(s, old, length);
	}
	s[length] = 0;
	return s;
}
