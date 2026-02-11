get_interface_meshparam(struct nl80211_state *state,
				   struct nl_cb *cb,
				   struct nl_msg *msg,
				   int argc, char **argv)
{
	const struct mesh_param_descr *mdescr = NULL;

	if (argc > 1)
		return 1;

	if (argc == 1) {
		mdescr = find_mesh_param(argv[0]);
		if (!mdescr)
			return 2;
	}

	nl_cb_set(cb, NL_CB_VALID, NL_CB_CUSTOM,
		  print_mesh_param_handler, (void *)mdescr);
	return 0;
}
