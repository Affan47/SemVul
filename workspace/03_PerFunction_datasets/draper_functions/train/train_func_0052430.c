Server_checkfortimeout()
{
	time_t now = time(NULL);


	if(Server->time_noserverpossible)
	{
		if((now - Server->time_noserverpossible) > Grufti->serverpossible_timeout)
		{
			Server_makeallunattempted();
			Server->time_noserverpossible = 0L;
		}
	}

	if(!Server_isconnected())
		return;


	if(Server->trying_server)
	{
		if((now - Server->trying_server) > Grufti->server_timeout)
		{
			char timedout[TIMESHORTLEN];

			Log_write(LOG_MAIN,"*","Timed out connecting to %s:%d.",Server_name(),Server_port());
			time_to_elap_short(Grufti->server_timeout,timedout);
			sprintf(Server->sbuf,"Timed out connecting (%s)",timedout);
			Server_setreason(Server->sbuf);
			Server->cur->flags |= SERV_CONNECT_FAILED;

			Server_disconnect();
		}
	}


	if(Server_waitingforpong())
	{

		if((now - Server->time_sent_ping) > Grufti->server_ping_timeout)
		{
			char pingedout[TIMESHORTLEN];


			time_to_elap_short(Grufti->server_ping_timeout,pingedout);
			Log_write(LOG_MAIN,"*","Server %s:%d pinged out. (no response in %s)",Server_name(),Server_port(),pingedout);


			Server_leavingIRC();

			sprintf(Server->sbuf,"Pinged out (after %s)",pingedout);
			Server_setreason(Server->sbuf);
			Server_disconnect();
		}
	}
	if(Server->flags & SERVER_QUIT_IN_PROGRESS)
	{

		if((now - Server->time_sent_quit) > Grufti->server_quit_timeout)
		{
			char timeout[TIMESHORTLEN];


			time_to_elap_short(Grufti->server_quit_timeout,timeout);

			Log_write(LOG_MAIN,"*","Server %s:%d pinged out (no QUIT in %s)",Server_name(),Server_port(),timeout);

			sprintf(Server->sbuf,"Pinged out (no QUIT in %s)",timeout);
			Server_leavingIRC();

			Server_setreason(Server->sbuf);
			Server_disconnect();
		}
	}

	if(Notify_waitingfor302())
	{
		if((now - Notify->last_radiated_msg) > Grufti->radiate_timeout)
		{

			Notify_dumpqueue();
		}
	}
}
