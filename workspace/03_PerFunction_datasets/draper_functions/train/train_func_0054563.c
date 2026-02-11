html_getmpline(char *buf, const int nocr)
{
	int	result = 0, ch;

	while  ((ch = getchar()) != EOF)  {
		if  (ch == '\r'  &&  nocr)
			continue;
		buf[result] = ch;
		if  (++result >= HINILWIDTH-1)
			break;
		if  (ch == '\n')
			break;
	}
	buf[result] = '\0';
	return  result;
}
