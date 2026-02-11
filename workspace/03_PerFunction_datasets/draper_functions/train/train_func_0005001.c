handle_cli_iax2_show_channels(struct ast_cli_entry *e, int cmd, struct ast_cli_args *a)
{
#define FORMAT2 "%-20.20s  %-15.15s  %-10.10s  %-11.11s  %-11.11s  %-7.7s  %-6.6s  %-6.6s  %s  %s  %9s\n"
#define FORMAT  "%-20.20s  %-15.15s  %-10.10s  %5.5d/%5.5d  %5.5d/%5.5d  %-5.5dms  %-4.4dms  %-4.4dms  %-6.6s  %s%s  %3s%s\n"
#define FORMATB "%-20.20s  %-15.15s  %-10.10s  %5.5d/%5.5d  %5.5d/%5.5d  [Native Bridged to ID=%5.5d]\n"
	int x;
	int numchans = 0;
	char first_message[10] = { 0, };
	char last_message[10] = { 0, };

	switch (cmd) {
	case CLI_INIT:
		e->command = "iax2 show channels";
		e->usage =
			"Usage: iax2 show channels\n"
			"       Lists all currently active IAX channels.\n";
		return NULL;
	case CLI_GENERATE:
		return NULL;
	}

	if (a->argc != 3)
		return CLI_SHOWUSAGE;
	ast_cli(a->fd, FORMAT2, "Channel", "Peer", "Username", "ID (Lo/Rem)", "Seq (Tx/Rx)", "Lag", "Jitter", "JitBuf", "Format", "FirstMsg", "LastMsg");
	for (x = 0; x < ARRAY_LEN(iaxs); x++) {
		ast_mutex_lock(&iaxsl[x]);
		if (iaxs[x]) {
			int lag, jitter, localdelay;
			jb_info jbinfo;
			if (ast_test_flag64(iaxs[x], IAX_USEJITTERBUF)) {
				jb_getinfo(iaxs[x]->jb, &jbinfo);
				jitter = jbinfo.jitter;
				localdelay = jbinfo.current - jbinfo.min;
			} else {
				jitter = -1;
				localdelay = 0;
			}

			iax_frame_subclass2str(iaxs[x]->first_iax_message & ~MARK_IAX_SUBCLASS_TX, first_message, sizeof(first_message));
			iax_frame_subclass2str(iaxs[x]->last_iax_message & ~MARK_IAX_SUBCLASS_TX, last_message, sizeof(last_message));
			lag = iaxs[x]->remote_rr.delay;
			ast_cli(a->fd, FORMAT,
				iaxs[x]->owner ? ast_channel_name(iaxs[x]->owner) : "(None)",
				ast_inet_ntoa(iaxs[x]->addr.sin_addr),
				S_OR(iaxs[x]->username, "(None)"),
				iaxs[x]->callno, iaxs[x]->peercallno,
				iaxs[x]->oseqno, iaxs[x]->iseqno,
				lag,
				jitter,
				localdelay,
				iax2_getformatname(iaxs[x]->voiceformat),
				(iaxs[x]->first_iax_message & MARK_IAX_SUBCLASS_TX) ? "Tx:" : "Rx:",
				first_message,
				(iaxs[x]->last_iax_message & MARK_IAX_SUBCLASS_TX) ? "Tx:" : "Rx:",
				last_message);
			numchans++;
		}
		ast_mutex_unlock(&iaxsl[x]);
	}
	ast_cli(a->fd, "%d active IAX channel%s\n", numchans, (numchans != 1) ? "s" : "");
	return CLI_SUCCESS;
#undef FORMAT
#undef FORMAT2
#undef FORMATB
}
