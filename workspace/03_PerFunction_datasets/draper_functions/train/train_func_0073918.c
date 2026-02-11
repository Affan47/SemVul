warning(char *s)
{
	char raw[80];
	char c = toupper(*s);
	if ( !(asmflags & F_NOWARNING) )
	{	sprintf(raw,"%7d WARNING: %c%s",linenumber,c,s+1);
		for ( s=raw; s[1]==' '; s++ )
			s[0]='>';
		outputraw(raw);
	}
}
