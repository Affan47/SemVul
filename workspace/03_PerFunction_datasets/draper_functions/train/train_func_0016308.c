sigchase(dns_message_t *msg) {
#if DIG_SIGCHASE_TD
	if (current_lookup->do_topdown) {
		sigchase_td(msg);
		return;
	}
#endif
#if DIG_SIGCHASE_BU
	sigchase_bu(msg);
	return;
#endif
}
