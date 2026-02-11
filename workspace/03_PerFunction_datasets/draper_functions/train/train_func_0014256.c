match_comma(char *patt)
{
	while  (*patt  &&  *patt != ',')  {
		if  (*patt == '[')  {
			do  patt++;
			while  (*patt  &&  *patt != ']');
		}
		if  (!*patt)
			return  (char *) 0;
		patt++;
	}
	if  (!*patt)
		return  (char *) 0;
	return  patt;
}
