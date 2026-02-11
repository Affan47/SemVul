handle_login(Octstr *packet, Octstr *out, int sequence) {
	Octstr *user = eat_string_parm(packet, 10, 32);
	Octstr *pass = eat_string_parm(packet, 11, 32);

	if (user == NULL)
		user = octstr_create("");
	if (pass == NULL)
		pass = octstr_create("");

	if (logging == LOG_packets)
		printf("RCV: Login user '%s', password '%s'\n",
			octstr_get_cstr(user), octstr_get_cstr(pass));

	if (octstr_str_compare(user, username) == 0 &&
	    octstr_str_compare(pass, password) == 0) {
		if (logging == LOG_packets)
			printf("SND: Login OK\n");
		send_packet(out, 51, sequence, 0);
	} else {
		send_error(out, 51, sequence, "100", "invalid login");
	}

	octstr_destroy(user);
	octstr_destroy(pass);
}
