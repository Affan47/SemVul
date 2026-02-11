analyz(Void)
{
	register char *i;

	if(parlev != 0)
	{
		err("unbalanced parentheses, statement skipped");
		stkey = SUNKNOWN;
		lastch = sbuf - 1;
		return;
	}
	if(nextch+2<=lastch && nextch[0]=='i' && nextch[1]=='f' && nextch[2]=='(')
	{

		parlev = 1;
		for(i=nextch+3 ; i<=lastch; ++i)
			if(*i == (MYQUOTE))
			{
				while(*++i != MYQUOTE)
					;
			}
			else if(*i == '(')
				++parlev;
			else if(*i == ')')
			{
				if(--parlev == 0)
					break;
			}
		if(i >= lastch)
			stkey = SLOGIF;
		else if(i[1] == '=')
			stkey = SLET;
		else if( isdigit(i[1]) )
			stkey = SARITHIF;
		else	stkey = SLOGIF;
		if(stkey != SLET)
			nextch += 2;
	}
	else if(expeql)
	{
		if(expcom && nextch<lastch &&
		    nextch[0]=='d' && nextch[1]=='o')
		{
			stkey = SDO;
			nextch += 2;
		}
		else	stkey = SLET;
	}
	else if (parseen && nextch + 7 < lastch
			&& nextch[2] != 'u'
			&& nextch[0] == 'd' && nextch[1] == 'o'
			&& ((nextch[2] >= '0' && nextch[2] <= '9')
				|| nextch[2] == ','
				|| nextch[2] == 'w'))
		{
		stkey = SDO;
		nextch += 2;
		needwkey = 1;
		}

	else	{
		stkey = getkwd();
		if(stkey==SGOTO && lastch>=nextch)
			if(nextch[0]=='(')
				stkey = SCOMPGOTO;
			else if(isalpha_(* USC nextch))
				stkey = SASGOTO;
	}
	parlev = 0;
}
