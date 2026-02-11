serv_connect_ssl_callback(rb_fde_t *F, int status, void *data)
{
	struct Client *client_p = data;
	rb_fde_t *xF[2];
	rb_connect_sockaddr(F, (struct sockaddr *)&client_p->localClient->ip,
			    sizeof(client_p->localClient->ip));
	if(status != RB_OK)
	{

		serv_connect_callback(F, status, data);
		return;
	}
	if(rb_socketpair(AF_UNIX, SOCK_STREAM, 0, &xF[0], &xF[1], "Outgoing ssld connection") == -1)
	{
                report_error("rb_socketpair failed for server %s:%s",
			      client_p->name, log_client_name(client_p, SHOW_IP), errno);
		serv_connect_callback(F, RB_ERROR, data);
		return;

	}
	del_from_cli_fd_hash(client_p);
	client_p->localClient->F = xF[0];
	add_to_cli_fd_hash(client_p);

	client_p->localClient->ssl_ctl = start_ssld_connect(F, xF[1], rb_get_fd(xF[0]));
	SetSSL(client_p);
	serv_connect_callback(client_p->localClient->F, RB_OK, client_p);
}
