command_match(struct iptables_command_state *cs)
{
	struct xtables_match *m;
	size_t size;

	if (cs->invert)
		xtables_error(PARAMETER_PROBLEM,
			   "unexpected ! flag before --match");

	m = xtables_find_match(optarg, XTF_LOAD_MUST_SUCCEED, &cs->matches);
	size = IPT_ALIGN(sizeof(struct ipt_entry_match)) + m->size;
	m->m = xtables_calloc(1, size);
	m->m->u.match_size = size;
	strcpy(m->m->u.user.name, m->name);
	m->m->u.user.revision = m->revision;
	if (m->init != NULL)
		m->init(m->m);
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
