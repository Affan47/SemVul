qt_comment(s)
	char *s;
{
	if(s[0] == '#') return(TRUE);
	return((boolean)(!in_msg  && strlen(s) == NO_MSG));
}
