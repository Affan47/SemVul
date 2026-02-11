status_connect(Boolean connected)
{
	if (connected) {
		oia_boxsolid = IN_3270 && !IN_SSCP;
		do_ctlr();
		if (kybdlock & KL_AWAITING_FIRST)
			do_msg(NONSPECIFIC);
		else
			do_msg(BLANK);
		status_untiming();
	} else {
		oia_boxsolid = False;
		do_ctlr();
		do_msg(DISCONNECTED);
		status_uncursor_pos();
	}
}
