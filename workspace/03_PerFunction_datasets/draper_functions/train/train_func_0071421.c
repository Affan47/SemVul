send_chansess_pty_req(struct Channel *channel) {

	unsigned char* term = NULL;

	TRACE(("enter send_chansess_pty_req"))

	start_channel_request(channel, "pty-req");


	buf_putbyte(ses.writepayload, 0);


	term = getenv("TERM");
	if (term == NULL) {
		term = "vt100";
	}
	buf_putstring(ses.writepayload, term, strlen(term));


	put_winsize();


	put_termcodes();

	encrypt_packet();


	if (signal(SIGWINCH, sigwinch_handler) == SIG_ERR) {
		dropbear_exit("signal error");
	}
	TRACE(("leave send_chansess_pty_req"))
}
