set_user_roles(role_set_t * set, char *id)
{
	role_datum_t *r;
	unsigned int i;
	ebitmap_node_t *node;

	if (strcmp(id, "*") == 0) {
		free(id);
		yyerror("* is not allowed in user declarations");
		return -1;
	}

	if (strcmp(id, "~") == 0) {
		free(id);
		yyerror("~ is not allowed in user declarations");
		return -1;
	}

	if (!is_id_in_scope(SYM_ROLES, id)) {
		yyerror2("role %s is not within scope", id);
		free(id);
		return -1;
	}
	r = hashtab_search(policydbp->p_roles.table, id);
	if (!r) {
		yyerror2("unknown role %s", id);
		free(id);
		return -1;
	}


	ebitmap_for_each_bit(&r->dominates, node, i) {
		if (ebitmap_node_get_bit(node, i))
			if (ebitmap_set_bit(&set->roles, i, TRUE))
				goto oom;
	}
	free(id);
	return 0;
      oom:
	yyerror("out of memory");
	return -1;
}
