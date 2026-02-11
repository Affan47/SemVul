finish_parse_e(struct parser *p) {
	struct ego_item *e, *n;


	z_info->e_max = 0;
	e = parser_priv(p);
	while (e) {
		if (e->eidx > z_info->e_max)
			z_info->e_max = e->eidx;
		e = e->next;
	}


	e_info = mem_zalloc((z_info->e_max+1) * sizeof(*e));
	for (e = parser_priv(p); e; e = n) {
		memcpy(&e_info[e->eidx], e, sizeof(*e));
		n = e->next;
		if (n)
			e_info[e->eidx].next = &e_info[n->eidx];
		else
			e_info[e->eidx].next = NULL;
		mem_free(e);
	}
	z_info->e_max += 1;

	create_slay_cache(e_info);

	parser_destroy(p);
	return 0;
}
