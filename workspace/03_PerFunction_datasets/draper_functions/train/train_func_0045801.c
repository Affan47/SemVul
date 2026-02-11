command_match(struct iptables_command_state *cs)
{
	struct xtables_match *m;
	size_t size;

	if (cs->invert)
		xtables_error(PARAMETER_PROBLEM,
			   "unexpected ! flag before --match");

	m = xtables_find_match(optarg, XTF_LOAD_MUST_SUCCEED, &cs->matches);
	size = XT_ALIGN(sizeof(struct xt_entry_match)) + m->size;
	m->m = xtables_calloc(1, size);
	m->m->u.match_size = size;
	if (m->real_name == NULL) {
		strcpy(m->m->u.user.name, m->name);
	} else {
		strcpy(m->m->u.user.name, m->real_name);
		if (!(m->ext_flags & XTABLES_EXT_ALIAS))
			fprintf(stderr, "Notice: the %s match is converted into %s match "
			        "in rule listing and saving.\n", m->name, m->real_name);
	}
	m->m->u.user.revision = m->revision;

	xs_init_match(m);
	if (m == m->next)
		return;

	if (m->x6_options != NULL)
		opts = xtables_options_xfrm(iptables_globals.orig_opts, opts,
					    m->x6_options, &m->option_offset);
	else if (m->extra_opts != NULL)
		opts = xtables_merge_options(iptables_globals.orig_opts, opts,
					     m->extra_opts, &m->option_offset);
	if (opts == NULL)
		xtables_error(OTHER_PROBLEM, "can't alloc memory!");
}
