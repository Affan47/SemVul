DCC_gotircchatconnection(dccrec *ircchat_serv)


{
	dccrec	*d;
	IP	ip;
	int	sock;
	u_short port;
	char	s[MAXHOSTLENGTH], u[USERLEN], h[HOSTLEN];

	context;
	Log_write(LOG_DEBUG,"*","Got connection on irc chat server.  Answering.");

	sock = net_accept(ircchat_serv->socket,s,&ip,&port,0);
	Log_write(LOG_DEBUG,"*","Accepted.");
	context;
	if(sock == -1 && (errno == EAGAIN))
	{
	context;
		Log_write(LOG_CMD|LOG_DEBUG,"*","I%d %s %s - Bad connection on ircchat server: %s",ircchat_serv->socket,ircchat_serv->nick,ircchat_serv->uh,net_errstr());
	context;
		return;
	}

	context;
	if(sock < 0)
	{
		Log_write(LOG_CMD|LOG_DEBUG,"*","%s %s - Failed connect over ircchat server on socket %d: %s",ircchat_serv->nick,ircchat_serv->uh,ircchat_serv->socket,net_errstr());


		return;
	}


	context;
	d = DCC_addnewconnection(ircchat_serv->nick,ircchat_serv->uh,ip,sock,port,DCC_CLIENT|CLIENT_IRC_CHAT);
	if(d == NULL)
		return;

	splituh(u,h,d->uh);
	if(!isequal(h,s))
	{


	}

	Log_write(LOG_CMD,"*","I%d %s %s - DCC connect estab'd.",d->socket,d->nick,d->uh);

	context;

	if(ircchat_serv->flags & STAT_COMMAND_PENDING)
	{


		if((time(NULL) - ircchat_serv->commandtime) < Grufti->pending_command_timeout && isequal(ircchat_serv->commandfromnick, d->nick))
		{

			if((strlen(ircchat_serv->command) >= 4) && strncasecmp(ircchat_serv->command,"pass",4) == 0)
				Log_write(LOG_CMD,"*","I%d %s %s - <sent password>",d->socket,d->nick,d->uh);
			else
				Log_write(LOG_CMD,"*","I%d %s %s - \"%s\"",d->socket,d->nick,d->uh,ircchat_serv->command);

			DCC_docommand(d,ircchat_serv->command);
		}
	}
	else
		DCC_ondccchat(d);

	context;

	DCC_disconnect(ircchat_serv);
}
