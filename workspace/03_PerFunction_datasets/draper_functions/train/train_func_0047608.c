trim(char *s){
	size_t i;
	for(i = strlen(s); i > 0; i--)
		if (isspace((int) s[i]) || s[i] == '\0')
			s[i] = '\0';
		else
			break;

	return s;
}
