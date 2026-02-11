cmd_showmynote()
{
	userrec	*u_recp;
	nbody	*body;
	noterec	*n;
	char	sent[TIMESHORTLEN];

	context;
	if(!cmdinfo.isparam)
	{
		say("Usage: showmynote <user>");
		sayf(2,0,"Use this command to display your last Note sent to the specified User.");
		return;
	}

	context;
	if(!User_isknown(cmdinfo.tok1))
	{
		sayf(0,0,"The nick \"%s\" is not known to me.",cmdinfo.tok1);
		return;
	}

	context;
	u_recp = User_user(cmdinfo.tok1);
	if(!u_recp->registered)
	{
		sayf(0,0,"The user \"%s\" is not registered.  Since Notes can only be sent to registered users, they aren't going to have any Notes from you.  Sorry!",cmdinfo.tok1);
		return;
	}

	context;

	n = Note_lastnotefromnick(u_recp,cmdinfo.user,cmdinfo.from_n);

	context;

	if(n == NULL)
	{
		char fwd[25];

		fwd[0] = 0;
		if(u_recp->forward && u_recp->forward[0])
			sprintf(fwd," or forwarded");

		sayf(0,0,"No Notes could be found to %s from you!  (Or your last Note to %s has been read%s...)",u_recp->acctname,u_recp->acctname,fwd);

		return;
	}

	context;
	say("Your last Note to %s reads:",u_recp->acctname);
	timet_to_date_long(n->sent,sent);
	say("-----------------------------------------------------------------");
	if(isequal(n->finger,n->uh))
		sayf(0,0,"From: %s (%s)",n->nick,n->uh);
	else
	{
		say("From: %s \"%s\"",n->nick,n->finger);
		say("Host: %s",n->uh);
	}
	say("Sent: %s",sent);
	say("-");
	for(body=n->body; body!=NULL; body=body->next)
		say("%s",body->text);
	say("-----------------------------------------------------------------");
}
