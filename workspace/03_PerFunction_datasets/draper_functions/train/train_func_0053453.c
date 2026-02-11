Channel_resetallpointers()
{
	chanrec *chan;
	membrec *m;

	for(chan=Channel->channels; chan!=NULL; chan=chan->next)
	{
		for(m=chan->memberlist; m!=NULL; m=m->next)
		{
			m->user = User_user(m->nick);
			m->account = User_account(m->user,m->nick,m->uh);
		}
	}
}
