webcmd_putnote()
{
	userrec	*u;
	noterec	*n;
	char	flags[BUFSIZ];

	if(!Web->istok1)
		return;

	DCC_flags2str(Web->d->flags,flags);
	Log_write(LOG_RAW,"*","Checking for DONTSHOWPROMPT");
	Log_write(LOG_RAW,"*","flags: %s",flags);
	if(!(Web->d->flags & STAT_DONTSHOWPROMPT))
	{
		Log_write(LOG_RAW,"*","DONTSHOWPROMPT is OFF, setting...");


		Web->d->flags |= STAT_DONTSHOWPROMPT;
		DCC_flags2str(Web->d->flags,flags);
		Log_write(LOG_RAW,"*","flags: %s",flags);
	}


	if(isequal(Web->tok1,"<EOF>"))
	{

		Web->d->flags &= ~STAT_DONTSHOWPROMPT;


		sprintf(Web->display,"%s - Post Note",Web->title);
		openhtml(Web->display);
		websay_statusline();
		websay_menuline("Login");
		websay("<br><br>");
		websay("");
		websay("Note sent.  ");

		u = User_user(Web->tok2);
		if(u->registered)
		{

			if(User_informuserofnote(u,Web->account))
				websay("(%s is online...)  ",u->acctname);
		}

		websay("Thanks!<p>");

		closehtml();

		return;
	}


	u = User_user(Web->tok1);
	if(!u->registered)
	{

		sprintf(Web->display,"%s - Post Note",Web->title);
		openhtml(Web->display);
		websay_statusline();
		websay_menuline("Login");
		websay("<br><br>");
		websay("");

		websay("The nick \"%s\" does not belong to a registered user.",Web->tok1);
		Web->d->flags &= ~STAT_DONTSHOWPROMPT;
		closehtml();
		return;
	}

	if(!u->registered)
	{

		sprintf(Web->display,"%s - Post Note",Web->title);
		openhtml(Web->display);
		websay_statusline();
		websay_menuline("Login");
		websay("<br><br>");
		websay("");

		websay("The nick \"%s\" does not belong to a registered user.",Web->tok1);
		Web->d->flags &= ~STAT_DONTSHOWPROMPT;
		closehtml();
		return;
	}

	if(Web->istok2)
		split(NULL,Web->cmdparam);
	else
		strcpy(Web->cmdparam,"");

	n = Note_lastnotefromnick(u,Web->user,Web->user->acctname);
	if(n == NULL)
	{

		User_addnewnote(u,Web->user,Web->account,Web->cmdparam,NOTE_NEW);
		return;
	}

	if(u->forward && u->forward[0])
	{
		if(!(n->flags & NOTE_FORWARD))
		{
			n->flags |= NOTE_FORWARD;
			Note->numNotesQueued++;
		}
	}
	Note_addbodyline(n,Web->cmdparam);
}
