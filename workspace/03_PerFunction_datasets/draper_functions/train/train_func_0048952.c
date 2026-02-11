DCC_dosuccessfullogin(dccrec *d)
{
	int	new;
	locarec	*l;
	char	motd[256];

	context;
	d->flags &= ~STAT_PENDING_LOGIN;

	if(d->flags & STAT_WEBCLIENT)
		Log_write(LOG_CMD|LOG_RAW,"*","W%d %s %s - Logged in.",d->socket,d->nick,d->uh);
	else if(d->flags & STAT_GATEWAYCLIENT)
		Log_write(LOG_CMD|LOG_RAW,"*","G%d %s %s - Logged in.",d->socket,d->nick,d->uh);
	else
		Log_write(LOG_CMD|LOG_RAW,"*","T%d %s %s - Logged in.",d->socket,d->nick,d->uh);

	context;

	User_nickviatelneton(d->user,d);


	if(d->flags & STAT_GATEWAYCLIENT)
	{
		DCC_showprompt(d);
		return;
	}


	if(Grufti->show_motd_on_telnet)
	{
		if(!Grufti->show_motd_onlywhenchanged || !d->user->registered)
		{
			sprintf(motd,"%s/%s",Grufti->admindir,Grufti->motd_telnet);
			catfile(d,motd);
		}
		else if(d->user->seen_motd <= Grufti->motd_modify_date)
		{
			d->user->seen_motd = time(NULL);
			sprintf(motd,"%s/%s",Grufti->admindir,Grufti->motd_telnet);
			catfile(d,motd);
		}
		else
		{
			char when1[TIMELONGLEN], when2[TIMELONGLEN];
			timet_to_date_short(Grufti->motd_modify_date,when1);
			timet_to_date_short(d->user->seen_motd,when2);
			DCC_write(d,"");
			DCC_write(d,"MOTD unchanged since %s.  (Last read: %s)",when1,when2);
			DCC_write(d,"");
		}

	}

	context;


	l = Location_location(d->user->location);
	if(l != NULL)
		DCC_write(d,"Hello %s in %s!",d->user->acctname,l->city);
	else
		DCC_write(d,"Hello %s!",d->user->acctname);


	new = Note_numnew(d->user);
	if(!d->user->num_notes)
		DCC_write(d,"You have no new Notes.");
	else if(new)
		DCC_write(d,"You have %d new Note%s. (%d total)",new,new==1?"":"s",d->user->num_notes);
	else
		DCC_write(d,"You have no new Notes. (%d total)",d->user->num_notes);

	context;
	DCC_write(d,"");
	DCC_showprompt(d);


}
