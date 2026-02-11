sctp_listen_for_all(void)
{
	struct socket *sock = NULL;
	int result = -EINVAL;
	struct connection *con = nodeid2con(0, GFP_NOFS);
	int bufsize = NEEDED_RMEM;
	int one = 1;

	if (!con)
		return -ENOMEM;

	log_print("Using SCTP for communications");

	result = sock_create_kern(&init_net, dlm_local_addr[0]->ss_family,
				  SOCK_STREAM, IPPROTO_SCTP, &sock);
	if (result < 0) {
		log_print("Can't create comms socket, check SCTP is loaded");
		goto out;
	}

	result = kernel_setsockopt(sock, SOL_SOCKET, SO_RCVBUFFORCE,
				 (char *)&bufsize, sizeof(bufsize));
	if (result)
		log_print("Error increasing buffer space on socket %d", result);

	result = kernel_setsockopt(sock, SOL_SCTP, SCTP_NODELAY, (char *)&one,
				   sizeof(one));
	if (result < 0)
		log_print("Could not set SCTP NODELAY error %d\n", result);


	sock->sk->sk_user_data = con;
	con->sock = sock;
	con->sock->sk->sk_data_ready = lowcomms_data_ready;
	con->rx_action = sctp_accept_from_sock;
	con->connect_action = sctp_connect_to_sock;


	if (sctp_bind_addrs(con, dlm_config.ci_tcp_port))
		goto create_delsock;

	result = sock->ops->listen(sock, 5);
	if (result < 0) {
		log_print("Can't set socket listening");
		goto create_delsock;
	}

	return 0;

create_delsock:
	sock_release(sock);
	con->sock = NULL;
out:
	return result;
}
