got352()


{
	chanrec *chan;
	membrec *m;

	context;

	str_element(Server->chname,Server->msg,2);
	str_element(Server->mode,Server->msg,7);

	context;

	chan = Channel_channel(Server->chname);
	if(chan == NULL)
	{
		Log_write(LOG_DEBUG,"*","Oops.  What am i doing on %s?",Server->chname);
		Server_write(PRIORITY_HIGH,"PART :%s",Server->chname);
		return;
	}

	context;

	str_element(Server->from_u, Server->msg,3);
	fixfrom(Server->from_u);
	str_element(Server->from_h, Server->msg,4);
	str_element(Server->from_n, Server->msg,6);
	sprintf(Server->from_uh,"%s@%s",Server->from_u,Server->from_h);
	sprintf(Server->from_nuh,"%s!%s",Server->from_n,Server->from_uh);

	context;

	m = Channel_member(chan,Server->from_n);
	context;
	if(m == NULL)
	{
		m = Channel_addnewmember(chan,Server->from_n,Server->from_uh);


		m->joined = 0L;


		m->last = 0L;
	}

	context;

	if(strchr(Server->mode,'@') != NULL)
		m->flags |= MEMBER_OPER;
	else
		m->flags &= ~MEMBER_OPER;

	context;

	if(strchr(Server->mode,'+') != NULL)
		m->flags |= MEMBER_VOICE;
	else
		m->flags &= ~MEMBER_VOICE;

	context;

	if(strchr(Server->mode,'G') != NULL)
		m->flags |= MEMBER_AWAY;
	else
		m->flags &= ~MEMBER_AWAY;
}
