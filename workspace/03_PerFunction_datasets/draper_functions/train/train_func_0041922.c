grecs_node_from_path_locus(const char *path, const char *value,
			   grecs_locus_t *plocus, grecs_locus_t *vallocus)
{
	int rc;
	int i;
	int argc;
	char **argv;
	struct grecs_node *dn = NULL;

	rc = split_cfg_path(path, &argc, &argv, NULL);
	if (rc)
		return NULL;

	dn = grecs_node_create(grecs_node_stmt, NULL);
	dn->ident = argv[argc - 1];
	if (value) {
		struct grecs_value *gval = parse_label(value);
		if (vallocus)
			gval->locus = *vallocus;
		dn->v.value = gval;
	} else
		dn->v.value = NULL;

	for (i = argc - 2; i >= 0; i--) {
		struct grecs_value *label = NULL;
		struct grecs_node *node;
		char *p, *q = argv[i];

		do {
			p = strchr(q, '=');
			if (p && p > argv[i] && p[-1] != '\\') {
				*p++ = 0;
				label = parse_label(p);
				break;
			} else if (p)
				q = p + 1;
			else
				break;
		} while (*q);

		node = grecs_node_create(grecs_node_block, plocus);
		node->ident = argv[i];
		if (label)
			node->v.value = label;

		node->down = dn;
		if (dn)
			dn->up = node;
		dn = node;
	}

	if (plocus)
		fixup_loci(dn,
			   plocus, vallocus ? &vallocus->end : NULL);

	free(argv);
	return dn;
}
