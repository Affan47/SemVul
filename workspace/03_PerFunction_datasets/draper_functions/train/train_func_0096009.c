command_idle(gboolean &sentdone) throw (imap_err)
{
	gboolean idleRenew = false;
	std::string line;
	do {
		idleRenew = false;
		sentdone = false;


		sendline ("IDLE");


		readline (line);
		if (line.find("+ ") != 0) throw imap_command_err();


		gint status = readline_ignoreinfo (line, true, false, true);
		if (status == SOCKET_TIMEOUT) {

			idleRenew = true;

			if (socket_->write (std::string("DONE\r\n")) != SOCKET_STATUS_OK)
				throw imap_socket_err();
			sentdone = true;

			status = readline_ignoreinfo (line, true, false, true);
			if (status != SOCKET_STATUS_OK)


				throw imap_socket_err();
			if (line.find (tag() + "OK") != 0)


				idleRenew = false;
		}
		else if (status != SOCKET_STATUS_OK) throw imap_socket_err();
	} while (idleRenew);

	return line;
}
