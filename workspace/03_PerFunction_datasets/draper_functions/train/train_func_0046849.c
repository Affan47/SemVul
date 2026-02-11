key_AID(unsigned char aid_code)
{
#if defined(X3270_ANSI)
	if (IN_ANSI) {
		register unsigned i;

		if (aid_code == AID_ENTER) {
			net_sendc('\r');
			return;
		}
		for (i = 0; i < PF_SZ; i++)
			if (aid_code == pf_xlate[i]) {
				ansi_send_pf(i+1);
				return;
			}
		for (i = 0; i < PA_SZ; i++)
			if (aid_code == pa_xlate[i]) {
				ansi_send_pa(i+1);
				return;
			}
		return;
	}
#endif
#if defined(X3270_PLUGIN)
	plugin_aid(aid_code);
#endif

	if (IN_SSCP) {
		if (kybdlock & KL_OIA_MINUS)
			return;
		switch (aid_code) {
		case AID_CLEAR:

			break;
		case AID_ENTER:


			buffer_addr = cursor_addr;
			aid = aid_code;
			ctlr_read_modified(aid, False);
			status_ctlr_done();
			break;
		default:

			status_minus();
			kybdlock_set(KL_OIA_MINUS, "key_AID");
			return;
		}
		return;
	}

	status_twait();
	mcursor_waiting();
	insert_mode(False);
	kybdlock_set(KL_OIA_TWAIT | KL_OIA_LOCKED, "key_AID");
	aid = aid_code;
	ctlr_read_modified(aid, False);
	ticking_start(False);
	status_ctlr_done();
}
