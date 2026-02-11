do_ptyconfig (int mode, struct portconfig *pcp)
{
	struct portconfig *cur;

	print_action("do_ptyconfig");
	if (mode != OP_SETNOW) {
		if (do_nvtdata() != E_NORMAL) {
			sysmessage (MSG_WARNING,
				"Can't flush output buffer before configure\n");
		}
	}

	if (mode == OP_SETFLUSH) {

		if (Pty.outbuff->b_hold) {
			RESET_BUFFER(Pty.outbuff);
			pn_wrok();
		}
	}


	cur = &Pty.comport->portconfig;

	if (memcmp ((void *) cur, (void *) pcp,  sizeof (struct portconfig))
					!= 0) {
		if (!pcp->speed) {
			PTY_SETSTATE("do_ptyconfig", PTY_WAITNVTCM);
			do_nvtdtroff();
		} else {
			PTY_SETSTATE("do_ptyconfig", PTY_CONFIG);
			do_nvtconfig(pcp);
		}
	} else {
		do_ptyconfig1();
	}

}
