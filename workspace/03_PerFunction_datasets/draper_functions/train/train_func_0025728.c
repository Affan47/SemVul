getnum(int signok)
{
	Posn n=0;
	int c, sign;

	sign = 1;
	if(signok>1 && nextc()=='-'){
		sign = -1;
		getch();
	}
	if((c=nextc())<'0' || '9'<c)
		return sign;
	while('0'<=(c=getch()) && c<='9')
		n = n*10 + (c-'0');
	ungetch();
	return sign*n;
}
