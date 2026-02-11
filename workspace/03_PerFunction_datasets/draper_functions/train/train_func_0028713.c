Server_display()
{
	servrec *serv;
	char lag[TIMESHORTLEN], retry[TIMESHORTLEN], unab[TIMESHORTLEN];
	char in[TIMESHORTLEN], out[TIMESHORTLEN], status[256];
	time_t serv_lag;


	if(Server->flags & SERVER_CONNECTED)
	{
		say("Server: %s %d",Server_name(),Server_port());
		if(!(Server->flags & SERVER_ACTIVITY))
			sprintf(status,"Connected, waiting for signs of life...");
		else if(!(Server->flags & SERVER_ACTIVEIRC))
			sprintf(status,"Connected, waiting to be welcomed to IRC...");
		else if(Server->flags & SERVER_QUIT_IN_PROGRESS)
			sprintf(status,"Waiting for server to shut down...");
		else
			sprintf(status,"Connected and active on IRC.");

		say("Status: %s",status);


		if(Server_waitingforpong())
			serv_lag = time(NULL) - Server->time_sent_ping;
		else
			serv_lag = Server->lag;
		time_to_elap_short(serv_lag,lag);
		say("Current nick: %-30s  Current lag: %s",Server->currentnick,lag);
	}


	else
	{
		say("Server: <not connected>");

		if(Grufti->irc == OFF)
			say("IRC is set to OFF.");
		else if(Server->num_servers)
		{
			if(Server->time_noserverpossible)
			{
				timet_to_ago_short(Server->time_noserverpossible,unab);
				time_to_elap_short(Grufti->serverpossible_timeout - (time(NULL) - Server->time_noserverpossible),retry);
				if(retry[0] == '-')
					strcpy(retry,"0s");
				say("Unable to connect to any servers for %s (retry in %s)",unab,retry);
			}
			else
				say("Trying %s:%d...",Server_name(),Server_port());
		}
	}

	bytes_to_kb_short(Server->bytes_in,in);
	bytes_to_kb_short(Server->bytes_out,out);
	say("Total in/out: %s in, %s out",in,out);
	say("");
	if(Server->serverlist)
	{
		if(Server->flags & SERVER_SHOW_REASONS)
		{
			say("  Server                        Reason for disconnect");
			say("------------------------------- ---------------------------------");
			for(serv=Server->serverlist; serv!=NULL; serv=serv->next)
				servrec_display(serv);
			say("------------------------------- ---------------------------------");
		}
		else
		{
			say("  Server                         Port Con'd AvLag    In   Out Net");
			say("------------------------------- ----- ----- ----- ----- ----- ---");
			for(serv=Server->serverlist; serv!=NULL; serv=serv->next)
				servrec_display(serv);
			say("------------------------------- ----- ----- ----- ----- ----- ---");
		}
	}
	else
		say("No servers configured.");
}
