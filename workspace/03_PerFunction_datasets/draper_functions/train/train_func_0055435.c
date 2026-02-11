_parse_pbs_nodes_opts(char *node_opts)
{
	int i = 0;
	char *temp = NULL;
	int ppn = 0;
	int node_cnt = 0;
	hostlist_t hl = hostlist_create(NULL);

	while(node_opts[i]) {
		if (!strncmp(node_opts+i, "ppn=", 4)) {
			i+=4;
			ppn += strtol(node_opts+i, NULL, 10);
			_get_next_pbs_node_part(node_opts, &i);
		} else if (isdigit(node_opts[i])) {
			node_cnt += strtol(node_opts+i, NULL, 10);
			_get_next_pbs_node_part(node_opts, &i);
		} else if (isalpha(node_opts[i])) {
			temp = _get_pbs_node_name(node_opts, &i);
			hostlist_push(hl, temp);
			xfree(temp);
		} else
			i++;

	}

	if (!node_cnt)
		node_cnt = 1;
	else {
		opt.nodes_set = true;
		opt.min_nodes = opt.max_nodes = node_cnt;
	}

	if (ppn) {
		ppn *= node_cnt;
		opt.ntasks_set = true;
		opt.ntasks = ppn;
	}

	if (hostlist_count(hl) > 0) {
		xfree(opt.nodelist);
		opt.nodelist = hostlist_ranged_string_xmalloc(hl);
#ifdef HAVE_BG
		info("\tThe nodelist option should only be used if\n"
		     "\tthe block you are asking for can be created.\n"
		     "\tPlease consult smap before using this option\n"
		     "\tor your job may be stuck with no way to run.");
#endif
	}

	hostlist_destroy(hl);
}
