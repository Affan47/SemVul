change_bool(char *name, int state, policydb_t * p, FILE * fp)
{
	cond_bool_datum_t *bool;

	bool = hashtab_search(p->p_bools.table, name);
	if (bool == NULL) {
		fprintf(fp, "Could not find bool %s\n", name);
		return -1;
	}
	bool->state = state;
	evaluate_conds(p);
	return 0;
}
