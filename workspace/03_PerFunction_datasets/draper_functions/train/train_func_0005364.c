cmd_setplan_helper(int line)
{
	char *p, *q, c;

	p = cmdinfo.param;


	if(*p == '.')
		p++;

	while(strlen(p) > LENGTH_PLANLINE)
	{
		q = p + LENGTH_PLANLINE;


		while((*q != ' ') && (q != p))
			q --;
		if(q == p)
			q = p + LENGTH_PLANLINE;
		c = *q;
		*q = 0;
		userrec_setplanx(cmdinfo.user,p,line);
		line++;
		if(line > NUMPLANLINES)
			return;
		*q = c;

		p = (c == ' ') ? q + 1 : q;
	}


	if(*p)
		userrec_setplanx(cmdinfo.user,p,line);
}
