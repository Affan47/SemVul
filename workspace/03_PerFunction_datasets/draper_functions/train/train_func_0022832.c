gob_str_delete_quotes(char *str)
{
	char *p, *i;
	p=i=str;
	while(*p!='\0')
	{
		if(*p=='\"')
		{
			p++;
			continue;
		}
		*i=*p;
		p++; i++;
	}
	*i=*p;
	return str;
}
