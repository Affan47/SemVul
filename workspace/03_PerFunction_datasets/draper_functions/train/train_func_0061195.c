finish_parse_s(struct parser *p) {
	struct spell *s, *n, *ss;
	struct object_kind *k;


	z_info->s_max = 0;
	s = parser_priv(p);
	while (s) {
		if (s->sidx > z_info->s_max)
			z_info->s_max = s->sidx;
		s = s->next;
	}


	s_info = mem_zalloc((z_info->s_max+1) * sizeof(*s));
	for (s = parser_priv(p); s; s = n) {
		n = s->next;

		ss = &s_info[s->sidx];
		memcpy(ss, s, sizeof(*s));
		k = objkind_get(s->tval, s->sval);
		if (k) {
			ss->next = k->spells;
			k->spells = ss;
		} else {
			ss->next = NULL;
		}
		mem_free(s);
	}
	z_info->s_max += 1;

	parser_destroy(p);
	return 0;
}
