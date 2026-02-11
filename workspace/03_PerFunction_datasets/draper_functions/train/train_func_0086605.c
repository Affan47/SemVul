html_iniint(const char *parname, const int deflt)
{
	long	result = 0, r2 = 0, r3 = 0;
	char	*cp;
	char	inbuf[HINILWIDTH];

	if  (!html_iniparam(parname, inbuf)  ||  !isdigit(inbuf[0]))
		return  deflt * 24L * 3600L;

	cp = inbuf;
	while  (isdigit(*cp))
		result = result*10 + *cp++ - '0';


	if  (*cp++ != ':' || !isdigit(*cp))
		return  result * 24L * 3600L;

	while  (isdigit(*cp))
		r2 = r2*10 + *cp++ - '0';


	if  (*cp++ != ':' || !isdigit(*cp))
		return  (result * 60 + r2) * 60;


	while  (isdigit(*cp))
		r3 = r3*10 + *cp++ - '0';

	return  ((result * 24 + r2) * 60 + r3) * 60;
}
