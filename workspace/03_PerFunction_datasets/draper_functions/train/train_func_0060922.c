DumpType( char *s, FILE *f, char *file, int line )
#else
DumpType( s, f, file, line )
char *s;
FILE *f;
char *file;
int line;
#endif
{
	char *p, *end;
	require(s!=NULL, "DumpType: invalid type string");

	p = &s[strlen(s)-1];

	while ( !isalnum(*p) && *p!='_' ) --p;

	while ( isalnum(*p) || *p=='_' ) --p;
	if ( p<=s )
	{
		warnFL(eMsg1("invalid parameter/return value: '%s'",s), file, line);
		return;
	}
	end = p;
	p = s;
	while ( p!=end ) {putc(*p, f); p++;}
	while ( *p!='\0' )
	{
		if ( !isalnum(*p) && *p!='_' ) putc(*p, f);
		p++;
	}
}
