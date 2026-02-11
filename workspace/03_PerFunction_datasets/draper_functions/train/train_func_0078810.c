error_exit_client(struct Client *client_p, int error)
{


	char errmsg[255];
	int current_error = rb_get_sockerr(client_p->localClient->F);

	SetIOError(client_p);

	if(IsServer(client_p) || IsHandshake(client_p))
	{
		int connected = rb_current_time() - client_p->localClient->firsttime;

		if(error == 0)
		{
			sendto_realops_flags(UMODE_ALL, L_ALL,
					     "Server %s closed the connection", client_p->name);

			ilog(L_SERVER, "Server %s closed the connection",
			     log_client_name(client_p, SHOW_IP));
		}
		else
		{
			report_error("Lost connection to %s: %s",
				     client_p->name,
				     log_client_name(client_p, SHOW_IP), current_error);
		}

		sendto_realops_flags(UMODE_ALL, L_ALL,
				     "%s had been connected for %d day%s, %2d:%02d:%02d",
				     client_p->name, connected / 86400,
				     (connected / 86400 == 1) ? "" : "s",
				     (connected % 86400) / 3600,
				     (connected % 3600) / 60, connected % 60);
	}

	if(error == 0)
		rb_strlcpy(errmsg, "Remote host closed the connection", sizeof(errmsg));
	else
		rb_snprintf(errmsg, sizeof(errmsg), "Read error: %s", strerror(current_error));

	exit_client(client_p, client_p, &me, errmsg);
}
