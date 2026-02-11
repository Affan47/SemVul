escape_forced_address (char *mask)
{
	char *username;
	char *escaped, *e;
	const char *p;
	int len;

	username = get_username();

	len = 0;
	for (p=mask ; *p ; p++)
	{
		if ( *p == '%' )
		{
			p++;
			if( !*p )
				break;
			switch( *p ) {
				case '%':
					len++;
					break;
				case 'u':
					len += strlen(username);
					break;
			}
		}
		else
			len++;
	}

	e = escaped = xmalloc(len+1);
	for (p=mask ; *p ; p++)
	{
		if (*p == '%')
		{
			p++;
			if (!*p)
				break;
			if (*p == '%')
				*(e++) = *p;
			else if (*p == 'u')
			{
				strcpy(e,username);
				e += strlen(username);
			}
		}
		else
		{
			*(e++) = *p;
			continue;
		}
	}
	*e = '\0';
	return escaped;

}
