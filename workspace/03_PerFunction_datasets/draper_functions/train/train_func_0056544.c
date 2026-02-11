do_ipaddr(char **argv)
{
	static const char commands[] ALIGN1 =
		"add\0""delete\0""list\0""show\0""lst\0""flush\0";
	smalluint cmd = 2;
	if (*argv) {
		cmd = index_in_substrings(commands, *argv);
		if (cmd > 5)
			bb_error_msg_and_die(bb_msg_invalid_arg, *argv, applet_name);
		argv++;
		if (cmd <= 1)
			return ipaddr_modify((cmd == 0) ? RTM_NEWADDR : RTM_DELADDR, argv);
	}

	return ipaddr_list_or_flush(argv, cmd == 5);
}
