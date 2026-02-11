finish_parse_a(struct parser *p) {
	struct artifact *a, *n;


	z_info->a_max = 0;
	a = parser_priv(p);
	while (a) {
		if (a->aidx > z_info->a_max)
			z_info->a_max = a->aidx;
		a = a->next;
	}


	a_info = mem_zalloc((z_info->a_max+1) * sizeof(*a));
	for (a = parser_priv(p); a; a = n) {
		memcpy(&a_info[a->aidx], a, sizeof(*a));
		n = a->next;
		if (n)
			a_info[a->aidx].next = &a_info[n->aidx];
		else
			a_info[a->aidx].next = NULL;

		mem_free(a);
	}
	z_info->a_max += 1;

	parser_destroy(p);
	return 0;
}
