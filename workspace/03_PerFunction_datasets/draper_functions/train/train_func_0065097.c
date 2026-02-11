recv_msg_userauth_info_request() {

	unsigned char *name = NULL;
	unsigned char *instruction = NULL;
	unsigned int num_prompts = 0;
	unsigned int i;

	unsigned char *prompt = NULL;
	unsigned int echo = 0;
	unsigned char *response = NULL;

	TRACE(("enter recv_msg_recv_userauth_info_request"))


	if (!cli_ses.interact_request_received) {
		fprintf(stderr, "Login for %s@%s\n", cli_opts.username,
				cli_opts.remotehost);
	}
	cli_ses.interact_request_received = 1;

	name = buf_getstring(ses.payload, NULL);
	instruction = buf_getstring(ses.payload, NULL);


	buf_eatstring(ses.payload);

	num_prompts = buf_getint(ses.payload);

	if (num_prompts >= DROPBEAR_MAX_CLI_INTERACT_PROMPTS) {
		dropbear_exit("Too many prompts received for keyboard-interactive");
	}


	CHECKCLEARTOWRITE();
	buf_putbyte(ses.writepayload, SSH_MSG_USERAUTH_INFO_RESPONSE);
	buf_putint(ses.writepayload, num_prompts);

	if (strlen(name) > 0) {
		cleantext(name);
		fprintf(stderr, "%s", name);
	}
	m_free(name);

	if (strlen(instruction) > 0) {
		cleantext(instruction);
		fprintf(stderr, "%s", instruction);
	}
	m_free(instruction);

	for (i = 0; i < num_prompts; i++) {
		unsigned int response_len = 0;
		prompt = buf_getstring(ses.payload, NULL);
		cleantext(prompt);

		echo = buf_getbool(ses.payload);

		if (!echo) {
			unsigned char* p = getpass_or_cancel(prompt);
			response = m_strdup(p);
			m_burn(p, strlen(p));
		} else {
			response = get_response(prompt);
		}

		response_len = strlen(response);
		buf_putstring(ses.writepayload, response, response_len);
		m_burn(response, response_len);
		m_free(response);
	}

	encrypt_packet();


	TRACE(("leave recv_msg_recv_userauth_info_request"))
}
