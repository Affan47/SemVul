DCC_forwardnotes(userrec *u, char *forward)
{
	dccrec	*emailclient;

	emailclient = DCC_addnewconnection(u->acctname,forward,hostnametoip(Grufti->smtp_gateway),0,25,DCC_CLIENT|CLIENT_SMTP);
	if(emailclient == NULL)
	{
		Log_write(LOG_ERROR,"*","%s - Couldn't connect to smtp server on %s.  Oh well.",u->acctname,Grufti->smtp_gateway);
		return 0;
	}

	emailclient->user = u;

	return 1;
}
