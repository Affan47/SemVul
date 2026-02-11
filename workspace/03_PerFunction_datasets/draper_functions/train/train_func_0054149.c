cstoctal(struct result *presult, char *s)
{
	register unsigned long val;
	register int r;

	val=0;
	while (*s)
	{	if ( *s<'0' || *s>'7' )
			error("bad octal number");
		r = *s-'0';
		if ( val> 0x1fffffff )
			error(overflow);
		val = (val<<3)+r;
		s++;
	};
	cst (presult,val);
}
