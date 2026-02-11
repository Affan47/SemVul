split_string_by_space(char *input, char **elem, int max) {
	int	no;
	char	*i=input;

	for(no=0;no<max;) {

		while(*i == ' ' || *i == '\t' || *i == '\r' || *i == '\n')
			*i++=0x0;
		if(*i == 0x0)
			break;

		elem[no++]=i;

		while(*i != ' ' && *i != '\t' && *i != 0x0)
			i++;

		if(*i == 0x0)
			break;
	}

	return no;
}
