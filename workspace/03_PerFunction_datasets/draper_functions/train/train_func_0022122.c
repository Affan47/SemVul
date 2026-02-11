NCstringTokenize(char *text,char ***tokens,char tok)
{
	register int pos = 0;
	int lpos = 0,strLen = strlen(text), numtokens = 0;

	(*tokens) = (char **) NULL;
	while (pos < strLen)
	{
		(*tokens) = realloc((*tokens),sizeof(char *) * (++numtokens));
		while ((pos < strLen) && (text[pos] != tok)) pos++;
		if(lpos == pos) (*tokens)[numtokens - 1] = (char *) NULL;
		else (*tokens)[numtokens - 1] = NCstringSubstr(text,lpos,pos - 1);

		lpos = ++pos;
	}
	return numtokens;
}
