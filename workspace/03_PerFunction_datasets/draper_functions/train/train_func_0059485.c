cmd_rn_display(u_long type)
{
	noterec	*n;
	char	save[20], read[20], subject[LINELENGTH], received[TIMESHORTLEN];
	char	finger[UHOSTLEN];
	int	num = 0;

	context;
	if(!cmdinfo.user->registered)
	{
		Log_write(LOG_ERROR,"*","User must be registered in order to read Notes.");
		return;
	}

	say(" #    Sent  From      Real Name               Subject");
	say("-- -- ----- --------- ----------------------- -------------------");
	context;
	for(n=cmdinfo.user->notes; n!=NULL; n=n->next)
	{
		num++;

		if(!(n->flags & type))
			continue;

		save[0] = 0;
		read[0] = 0;
		if(n->flags & NOTE_SAVE)
			strcpy(save,"*");
		if(n->flags & NOTE_NOTICE)
			strcpy(save,"!");
		if(n->flags & NOTE_NEW)
			strcpy(read,"N");
		else if(n->flags & NOTE_MEMO)
			strcpy(read,"m");
		else if(n->flags & NOTE_READ)
			strcpy(read," ");

		strcpy(finger,n->finger);
		if(strlen(finger) > 23)
			strcpy(&finger[23 - 3],"...");

		if(n->body != NULL && n->body->text != NULL)
			strcpy(subject,n->body->text);
		else
			strcpy(subject,"");
		if(strlen(subject) > 19)
			strcpy(&subject[19 - 3],"...");
		timet_to_dateonly_short(n->sent,received);
		received[5] = 0;

		say("%2d %1s%1s %5s %-9s %-23s %-19s",num,save,read,received,n->nick,finger,subject);
	}
	say("-- -- ----- --------- ----------------------- -------------------");
}
