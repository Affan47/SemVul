read_cond(FILE *inf)
{
	int	ch, cnt;
	char	linbuf[160];
	static	struct	condition	result;

	do  ch = getc(inf);
	while  (ch == ' ' || ch == '\t');

	if  (!isalpha(ch))  {
		err("Expecting variable name in cond");
		return  (struct condition *) 0;
	}
	cnt = 0;
	do  {
		if  (cnt < sizeof(linbuf) - 1)
			linbuf[cnt++] = (char) ch;
		ch = getc(inf);
	}  while  (isalnum(ch));
	linbuf[cnt] = '\0';
	result.cond_var = lookuphash(linbuf);

	while  (ch == ' ' || ch == '\t')
		ch = getc(inf);

	switch  (ch)  {
	default:
	badcond:
		err("Bad condition");
		return  (struct condition *) 0;

	case  ')':
	case  '}':
		result.cond_type = COND_DEF;
		result.cond_string = (char *) 0;
		return  &result;

	case  '=':
		do  ch = getc(inf);
		while  (ch == '=');
		result.cond_type = COND_EQ;
		goto  getstr;

	case  '~':
		do  ch = getc(inf);
		while  (ch == '=');
		result.cond_type = COND_MATCH;
		goto  getstr;

	case  '!':
		ch = getc(inf);
		if  (ch == '=')  {
			result.cond_type = COND_NEQ;
			goto  getstr;
		}
		if  (ch == '~')  {
			result.cond_type = COND_NONMATCH;
			goto  getstr;
		}
		err("Unknown operator");
		return  (struct condition *) 0;

	getstr:
		while  (ch == ' ' || ch == '\t')
			ch = getc(inf);
		cnt = 0;
		do  {
			if  (cnt < sizeof(linbuf) - 1)
				linbuf[cnt++] = (char) ch;
			ch = getc(inf);
		}  while  (ch != ')' && ch != '}' && ch != ' ' && ch != '\t' && ch != '\n' && ch != EOF);
		linbuf[cnt] = '\0';
		while  (ch == ' ' || ch == '\t')
			ch = getc(inf);
		if  (ch != ')'  &&  ch != '}')
			goto  badcond;


		result.cond_string = stracpy(linbuf);
		return  &result;
	}
}
