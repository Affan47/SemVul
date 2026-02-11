readmt(s)
char *s;
{
	int n = 0;
	char *p = s;
	int c;

	while ( n++<4 && (c=(*Mf_getc)()) != EOF ) {
		if ( c != *p++ ) {
			char buff[32];
			(void) strcpy(buff,"expecting ");
			(void) strcat(buff,s);
			mferror(buff);
		}
	}
	return(c);
}
