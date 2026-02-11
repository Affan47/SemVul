check_new_passwds(int force) {
	static time_t last_check = 0;
	time_t now;

	if (! passwdfile) {
		return;
	}
	if (strstr(passwdfile, "read:") != passwdfile) {
		return;
	}
	if (unixpw_in_progress) return;

	if (force) {
		last_check = 0;
	}

	now = time(NULL);
	if (now > last_check + 1) {
		if (read_passwds(passwdfile)) {
			install_passwds();
		}
		last_check = now;
	}
}
