realcompile(Rune *s)
{
	int token;

	startlex(s);
	atorp = atorstack;
	andp = andstack;
	subidp = subidstack;
	cursubid = 0;
	lastwasand = FALSE;

	pushator(START-1);
	while((token=lex()) != END){
		if((token&ISATOR) == OPERATOR)
			operator(token);
		else
			operand(token);
	}

	evaluntil(START);

	operand(END);
	evaluntil(START);
	if(nbra)
		regerror(Eleftpar);
	--andp;
	return andp->first;
}
