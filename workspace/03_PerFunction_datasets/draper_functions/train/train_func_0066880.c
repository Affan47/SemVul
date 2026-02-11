DCC_resetallpointers()
{
	dccrec *d;

	context;
	for(d=DCC->dcclist; d!=NULL; d=d->next)
	{
		if((d->flags & CLIENT_IRC_CHAT) || (d->flags & CLIENT_SMTP) || ((d->flags & CLIENT_TELNET_CHAT) && !(d->flags & STAT_PENDING_LOGIN)))
		{
			d->user = User_user(d->nick);
			d->account = User_account(d->user,d->nick,d->uh);
		}
	}
}
