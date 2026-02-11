CMDgetDelim(char **in, size_t *len,char delim, FILE *file)
{
	char ch;
	if(*in == (char *) NULL) *in = (char *) malloc((*len = 1) * sizeof(char));
	else *in = (char *) realloc(*in,(*len = 1) * sizeof(char));
	ch = getc(file);
	while((ch != delim) && (ch != EOF) && (ch != '\0') && (ch != (char) NULL))
	{
		(*in)[*len - 1] = ch;
		*in = (char *) realloc(*in,++(*len) * sizeof(char));
		ch = getc(file);
	}
	(*in)[*len - 1] = '\0';
	if((ch == (char) NULL) || (ch == '\0')) return -1;
	return (int) (*len) - 1;
}
