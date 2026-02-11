isdotdot(p)
register char	*p;
{
	if(p && *p++ == '.' && *p++ == '.' && *p++ == '\0')
		return(TRUE);
	return(FALSE);
}
