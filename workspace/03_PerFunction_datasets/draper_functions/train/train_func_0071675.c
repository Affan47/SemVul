got_usr1(int z)
{
	dccrec *d, *d_next;
	char	signoff[100];

	if(Grufti->die)
	{
		Log_write(LOG_ALL,"*","Received another soft kill while waiting for signoff.  Exiting via TERM.");
		got_term(z);
	}

	strcpy(signoff,"Soft kill requested, signing off.");
	Log_write(LOG_ALL,"*","Soft kill requested, signing off.");

	Grufti->die = 1;


	if(Server_isactiveIRC())
	{
		Log_write(LOG_MAIN,"*","Sent QUIT, waiting for signoff...");
		Server_quit(signoff);
	}
	else if(Server_isconnected())
	{
		Server_disconnect();
		Log_write(LOG_MAIN,"*","Signing off...");
	}
	else
		Log_write(LOG_MAIN,"*","Signing off...");


	d = DCC->dcclist;
	while(d != NULL)
	{
		d_next = d->next;
		DCC_bootuser(d,signoff);
		d = d_next;
	}


}
