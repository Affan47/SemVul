update_siginfo_msg(time_t exp, const char *srv)
{

    memset(siginfo_msg, 0, sizeof(siginfo_msg));
    memcpy(&siginfo_msg, "Updating...\n", sizeof("Updating...\n"));
    if (exp) {
	if (srv == NULL) {
	    snprintf(siginfo_msg, sizeof(siginfo_msg),
		     N_("kinit: TGT expires in %llu seconds\n", ""),
		     (unsigned long long)expire);
	} else {
	    snprintf(siginfo_msg, sizeof(siginfo_msg),
		     N_("kinit: Ticket for %s expired\n", ""), srv);
	}
	return;
    }


    if (srv == NULL) {
	snprintf(siginfo_msg, sizeof(siginfo_msg),
		 N_("kinit: TGT expired\n", ""));
    } else {
	snprintf(siginfo_msg, sizeof(siginfo_msg),
		 N_("kinit: Ticket for %s expired\n", ""), srv);
    }
}
