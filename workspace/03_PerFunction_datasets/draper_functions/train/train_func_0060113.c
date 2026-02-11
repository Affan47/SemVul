check_control(s)
	char	*s;
{
	int	i;

	if(s[0] != '%') return(-1);

	for(i = 0; deflist[i].defname; i++)
	    if(!strncmp(deflist[i].defname, s+1, strlen(deflist[i].defname)))
		return(i);

	return(-1);
}
