DCC_gotinternalconnection(dccrec *gw_serv)
{
	char	s[MAXHOSTLENGTH];
	char	uh[HOSTLEN];
	int	sock;
	u_short port;
	IP	ip;
	dccrec	*d;


	sock = net_accept(gw_serv->socket,s,&ip,&port,0);
	if(sock == -1 && (errno == EAGAIN))
	{
		Log_write(LOG_CMD|LOG_DEBUG,"*","G%d %s %s - Bad connection on gateway server: %s",gw_serv->socket,gw_serv->nick,gw_serv->uh,net_errstr());
		return;
	}

	context;
	if(sock < 0)
	{
		Log_write(LOG_CMD|LOG_DEBUG,"*","Incoming gateway failed connect on socket %d: %s",gw_serv->socket,net_errstr());
		return;
	}
	context;


	Log_write(LOG_CMD,"*","Gateway connection from %s.",s);
	sprintf(uh,"gateway@%s",s);


	d = DCC_addnewconnection("\"pending\"",uh,ip,sock,port,DCC_CLIENT|CLIENT_TELNET_CHAT|STAT_GATEWAYCLIENT|STAT_PENDING_LOGIN);
	context;
	if(d == NULL)
	{
		internal("Unable to find recently added connection on %s %d %d", uh,
			port, sock);
		return;
	}


	d->flags |= STAT_WAITINGFORID;
	context;
}
