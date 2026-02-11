connect (void) throw (imap_err)
{

	reset_tag();

#ifdef DEBUG
	g_message ("[%d] Trying to connect to %s on port %d", uin(),
			   address().c_str(), port());
#endif


	if (authentication() == AUTH_AUTODETECT) {
		guint prt = port();
		if (!use_other_port())
			prt = 993;
		if (!socket_->open (address(), prt, AUTH_SSL)) {
			if (!use_other_port())
				prt = 143;
			if (!socket_->open (address(), prt, AUTH_USER_PASS))
				throw imap_socket_err();
			else {
				port (prt);
				authentication (AUTH_USER_PASS);
				socket_->close();
			}
		}
		else {
			port (prt);
			authentication (AUTH_SSL);
			socket_->close();
		}
	}


	if (!socket_->open (address(), port(), authentication(), certificate(), 3))
		throw imap_socket_err();


	socket_->set_read_timeout(delay() < 60 ? 60 : delay());

#ifdef DEBUG
	g_message ("[%d] Connected to %s on port %d", uin(),
			   address().c_str(), port());
#endif


	ok_response_codes_.clear ();
	std::string line;
	readline (line);


	command_capability (true);


	command_login();


	command_select();
}
