gotmsg()


{
	char *p, *p1;
	int ctcp = 0;

	context;

	str_element(Server->to,Server->msg,1);
	strcpy(Server->sbuf,Server->msg);
	split(NULL,Server->sbuf);
	fixcolon(Server->sbuf);

	context;

	p = strchr(Server->sbuf,1);
	while(p != NULL)
	{
		ctcp = 1;
		p++;
		p1 = p;
		while((*p != 1) && (*p != 0))
			p++;
		if(*p == 1)
		{
			*p = 0;
			strcpy(Server->msg,p1);
			strcpy(p1-1,p+1);
		}
		else
		{
			strcpy(Server->msg,p1);
			strcpy(p1-1,p);
		}
		gotctcp();

		p = strchr(Server->sbuf,1);
	}
	if(ctcp)
		return;

	context;
	strcpy(Server->msg,Server->sbuf);


	if((Server->to[0] == '#') || (Server->to[0] == '&') || (Server->to[0] == '+'))
		gotpublic();


	else if((Server->to[0] == '$') || (strchr(Server->to,'.')!=NULL))
		gotoper();


	else
		gotprivate();
}
