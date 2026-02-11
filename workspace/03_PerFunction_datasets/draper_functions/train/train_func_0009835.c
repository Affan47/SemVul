define_common_perms(void)
{
	char *id = 0, *perm = 0;
	common_datum_t *comdatum = 0;
	perm_datum_t *perdatum = 0;
	int ret;

	if (pass == 2) {
		while ((id = queue_remove(id_queue)))
			free(id);
		return 0;
	}

	id = (char *)queue_remove(id_queue);
	if (!id) {
		yyerror("no common name for common perm definition?");
		return -1;
	}
	comdatum = hashtab_search(policydbp->p_commons.table, id);
	if (comdatum) {
		yyerror2("duplicate declaration for common %s\n", id);
		return -1;
	}
	comdatum = (common_datum_t *) malloc(sizeof(common_datum_t));
	if (!comdatum) {
		yyerror("out of memory");
		goto bad;
	}
	memset(comdatum, 0, sizeof(common_datum_t));
	ret = hashtab_insert(policydbp->p_commons.table, (hashtab_key_t) id, (hashtab_datum_t) comdatum);

	if (ret == SEPOL_EEXIST) {
		yyerror("duplicate common definition");
		goto bad;
	}
	if (ret == SEPOL_ENOMEM) {
		yyerror("hash table overflow");
		goto bad;
	}
	comdatum->s.value = policydbp->p_commons.nprim + 1;
	if (symtab_init(&comdatum->permissions, PERM_SYMTAB_SIZE)) {
		yyerror("out of memory");
		goto bad;
	}
	policydbp->p_commons.nprim++;
	while ((perm = queue_remove(id_queue))) {
		perdatum = (perm_datum_t *) malloc(sizeof(perm_datum_t));
		if (!perdatum) {
			yyerror("out of memory");
			goto bad_perm;
		}
		memset(perdatum, 0, sizeof(perm_datum_t));
		perdatum->s.value = comdatum->permissions.nprim + 1;

		if (perdatum->s.value > (sizeof(sepol_access_vector_t) * 8)) {
			yyerror("too many permissions to fit in an access vector");
			goto bad_perm;
		}
		ret = hashtab_insert(comdatum->permissions.table, (hashtab_key_t) perm, (hashtab_datum_t) perdatum);

		if (ret == SEPOL_EEXIST) {
			yyerror2("duplicate permission %s in common %s", perm, id);
			goto bad_perm;
		}
		if (ret == SEPOL_ENOMEM) {
			yyerror("hash table overflow");
			goto bad_perm;
		}
		comdatum->permissions.nprim++;
	}

	return 0;

      bad:
	if (id)
		free(id);
	if (comdatum)
		free(comdatum);
	return -1;

      bad_perm:
	if (perm)
		free(perm);
	if (perdatum)
		free(perdatum);
	return -1;
}
