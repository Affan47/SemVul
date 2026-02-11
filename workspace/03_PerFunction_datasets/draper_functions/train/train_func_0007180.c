got251()


{
	int found = 0;
	char num[SERVERLEN];

	context;
	split(NULL,Server->msg);
	fixcolon(Server->msg);

	context;

	if(Server_waitingforluser())
		Server->flags &= ~SERVER_WAITING_4_LUSER;
	else
		Log_write(LOG_MAIN,"*","%s",Server->msg);

	context;

	while(!found)
	{
		split(num,Server->msg);
		if(strncasecmp("server",Server->msg,6) == 0)
			found = 1;
	}

	context;
	if(Server->cur == NULL)
		return;

	context;
	if(found)
		Server->cur->num_servers = atoi(num);

	if(Grufti->min_servers && (Server->cur->num_servers < Grufti->min_servers))
	{
		Log_write(LOG_MAIN,"*","Only %d server%s visible from %s.  Need %d.",Server->cur->num_servers,Server->cur->num_servers==1?"":"s",Server_name(),Grufti->min_servers);

		Server_leavingIRC();

		sprintf(Server->sbuf,"Need %d servers. (Had %d)",Grufti->min_servers,Server->cur->num_servers);
		Server_setreason(Server->sbuf);
		Server_disconnect();
	}

}
