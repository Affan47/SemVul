recv_msg_service_accept() {

	unsigned char* servicename;
	unsigned int len;

	TRACE(("enter recv_msg_service_accept"))

	servicename = buf_getstring(ses.payload, &len);


	if (cli_ses.state == SERVICE_AUTH_REQ_SENT
			&& len == SSH_SERVICE_USERAUTH_LEN
			&& strncmp(SSH_SERVICE_USERAUTH, servicename, len) == 0) {

		cli_ses.state = SERVICE_AUTH_ACCEPT_RCVD;
		m_free(servicename);
		TRACE(("leave recv_msg_service_accept: done ssh-userauth"))
		return;
	}


	if (cli_ses.state == SERVICE_CONN_REQ_SENT
			&& len == SSH_SERVICE_CONNECTION_LEN
			&& strncmp(SSH_SERVICE_CONNECTION, servicename, len) == 0) {

		if (ses.authstate.authdone != 1) {
			dropbear_exit("request for connection before auth");
		}

		cli_ses.state = SERVICE_CONN_ACCEPT_RCVD;
		m_free(servicename);
		TRACE(("leave recv_msg_service_accept: done ssh-connection"))
		return;
	}

	dropbear_exit("unrecognised service accept");
}
