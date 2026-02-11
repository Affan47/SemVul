Server_gotactivity(char *buf)
{
	int bytes;
	coderec *code;


	if(!buf[0])
		return;

	if(Server->cur == NULL)
	{
		Log_write(LOG_DEBUG,"*","Shit.  Got activity on a server but cur is NULL!");
		return;
	}


	if(Server->trying_server)
	{
		Log_write(LOG_MAIN,"*","Connected to IRC server %s.  Waiting for welcome...",Server_name());
		Server->trying_server = 0L;
		Server->flags |= SERVER_ACTIVITY;
		Server->cur->first_activity = time(NULL);
		xfree(Server->cur->reason);
		Server->cur->reason = NULL;
	}


	bytes = strlen(buf);
	Server->cur->bytes_in += (u_long)bytes;
	Server->bytes_in += (u_long)bytes;


	Server_parsemsg(buf);

#ifdef RAW_LOGGING
	Log_write(LOG_RAW,"*","%s %s %s",Server->code,Server->from,Server->msg);
#endif


	code = Codes_code(Server->code);
	if(code != NULL)
	{
		code->function();
		code->accessed++;
	}
	else
		gotunknown();
}
