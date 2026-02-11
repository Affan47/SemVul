dominate_role_recheck(hashtab_key_t key, hashtab_datum_t datum,
				 void *arg)
{
	role_datum_t *rdp = (role_datum_t *) arg;
	role_datum_t *rdatum = (role_datum_t *) datum;
	ebitmap_node_t *node;
	int i;


	if (rdatum->s.value == rdp->s.value)
		return 0;


	if (ebitmap_get_bit(&(rdatum->dominates), rdp->s.value - 1)) {
		ebitmap_t types;
		ebitmap_init(&types);
		if (type_set_expand(&rdp->types, &types, policydbp, 1)) {
			ebitmap_destroy(&types);
			return -1;
		}

		ebitmap_for_each_bit(&rdp->dominates, node, i) {
			if (ebitmap_node_get_bit(node, i))
				if (ebitmap_set_bit
				    (&rdatum->dominates, i, TRUE))
					goto oom;
		}
		ebitmap_for_each_bit(&types, node, i) {
			if (ebitmap_node_get_bit(node, i))
				if (ebitmap_set_bit
				    (&rdatum->types.types, i, TRUE))
					goto oom;
		}
		ebitmap_destroy(&types);
	}


	return 0;
      oom:
	yyerror("Out of memory");
	return -1;
}
