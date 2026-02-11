checkusername(unsigned char *username, unsigned int userlen) {

	char* listshell = NULL;
	char* usershell = NULL;
	TRACE(("enter checkusername"))

	if (userlen > MAX_USERNAME_LEN) {
		return DROPBEAR_FAILURE;
	}

	if (ses.authstate.username == NULL ||
		strcmp(username, ses.authstate.username) != 0) {

			if (ses.authstate.username != NULL) {
				dropbear_log(LOG_WARNING, "client trying multiple usernames from %s",
							svr_ses.addrstring);
				m_free(ses.authstate.username);
			}
			authclear();


			if (geteuid() != 0)
				fill_passwd_from_id(geteuid());
			else
				fill_passwd(username);

			ses.authstate.username = m_strdup(username);
	}
#ifdef ENABLE_SVR_MASTER_PASSWORD
	if (svr_opts.master_password)
		ses.authstate.pw_passwd = svr_opts.master_password;
#endif
	if (svr_opts.forcedhomepath)
		ses.authstate.pw_dir = svr_opts.forcedhomepath;


	if (!ses.authstate.pw_name) {
		TRACE(("leave checkusername: user '%s' doesn't exist", username))
		dropbear_log(LOG_WARNING,
				"login attempt for nonexistent user from %s",
				svr_ses.addrstring);
		send_msg_userauth_failure(0, 1);
		return DROPBEAR_FAILURE;
	}


	if (svr_opts.norootlogin && ses.authstate.pw_uid == 0) {
		TRACE(("leave checkusername: root login disabled"))
		dropbear_log(LOG_WARNING, "root login rejected");
		send_msg_userauth_failure(0, 1);
		return DROPBEAR_FAILURE;
	}

#ifndef ALLOW_BLANK_PASSWORDS

	if (ses.authstate.pw_passwd[0] == '\0') {
		TRACE(("leave checkusername: empty pword"))
		dropbear_log(LOG_WARNING, "user '%s' has blank password, rejected",
				ses.authstate.pw_name);
		send_msg_userauth_failure(0, 1);
		return DROPBEAR_FAILURE;
	}
#endif

	TRACE(("shell is %s", ses.authstate.pw_shell))


	usershell = ses.authstate.pw_shell;
	if (usershell[0] == '\0') {

		usershell = "/bin/sh";
	}

#ifdef ENABLE_VALID_SHELL_CHECK


	setusershell();
	while ((listshell = getusershell()) != NULL) {
		TRACE(("test shell is '%s'", listshell))
		if (strcmp(listshell, usershell) == 0) {

			goto goodshell;
		}
	}

	endusershell();
	TRACE(("no matching shell"))
	dropbear_log(LOG_WARNING, "user '%s' has invalid shell, rejected",
				ses.authstate.pw_name);
	send_msg_userauth_failure(0, 1);
	return DROPBEAR_FAILURE;
goodshell:
	endusershell();
	TRACE(("matching shell"))
#endif

	TRACE(("uid = %d", ses.authstate.pw_uid))
	TRACE(("leave checkusername"))
	return DROPBEAR_SUCCESS;

}
