parse_ematch(int *argc_p, char ***argv_p, int tca_id, struct nlmsghdr *n)
{
	begin_argc = ematch_argc = *argc_p;
	begin_argv = ematch_argv = *argv_p;

	if (ematch_parse()) {
		int err = em_parse_error(EINVAL, NULL, NULL, NULL,
		    "Parse error");
		free_ematch_err();
		return err;
	}

	free_ematch_err();


	ematch_argc++;
	ematch_argv--;

	if (ematch_root) {
		struct rtattr *tail, *tail_list;

		struct tcf_ematch_tree_hdr hdr = {
			.nmatches = flatten_tree(ematch_root, ematch_root),
			.progid = TCF_EM_PROG_TC
		};

		tail = NLMSG_TAIL(n);
		addattr_l(n, MAX_MSG, tca_id, NULL, 0);
		addattr_l(n, MAX_MSG, TCA_EMATCH_TREE_HDR, &hdr, sizeof(hdr));

		tail_list = NLMSG_TAIL(n);
		addattr_l(n, MAX_MSG, TCA_EMATCH_TREE_LIST, NULL, 0);

		if (parse_tree(n, ematch_root) < 0)
			return -1;

		tail_list->rta_len = (void*) NLMSG_TAIL(n) - (void*) tail_list;
		tail->rta_len = (void*) NLMSG_TAIL(n) - (void*) tail;
	}

	*argc_p = ematch_argc;
	*argv_p = ematch_argv;

	return 0;
}
