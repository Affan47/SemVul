parse_categories(char *id, level_datum_t * levdatum, ebitmap_t * cats)
{
	cat_datum_t *cdatum;
	int range_start, range_end, i;

	if (id_has_dot(id)) {
		char *id_start = id;
		char *id_end = strchr(id, '.');

		*(id_end++) = '\0';

		cdatum = (cat_datum_t *) hashtab_search(policydbp->p_cats.table,
							(hashtab_key_t)
							id_start);
		if (!cdatum) {
			yyerror2("unknown category %s", id_start);
			return -1;
		}
		range_start = cdatum->s.value - 1;
		cdatum = (cat_datum_t *) hashtab_search(policydbp->p_cats.table,
							(hashtab_key_t) id_end);
		if (!cdatum) {
			yyerror2("unknown category %s", id_end);
			return -1;
		}
		range_end = cdatum->s.value - 1;

		if (range_end < range_start) {
			yyerror2("category range is invalid");
			return -1;
		}
	} else {
		cdatum = (cat_datum_t *) hashtab_search(policydbp->p_cats.table,
							(hashtab_key_t) id);
		if (!cdatum) {
			yyerror2("unknown category %s", id);
			return -1;
		}
		range_start = range_end = cdatum->s.value - 1;
	}

	for (i = range_start; i <= range_end; i++) {
		if (!ebitmap_get_bit(&levdatum->level->cat, i)) {
			uint32_t level_value = levdatum->level->sens - 1;
			policydb_index_others(NULL, policydbp, 0);
			yyerror2("category %s can not be associated "
				 "with level %s",
				 policydbp->p_cat_val_to_name[i],
				 policydbp->p_sens_val_to_name[level_value]);
			return -1;
		}
		if (ebitmap_set_bit(cats, i, TRUE)) {
			yyerror("out of memory");
			return -1;
		}
	}

	return 0;
}
