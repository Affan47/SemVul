gcide_match_all(struct gcide_db *db, const dico_strategy_t strat,
		const char *word)
{
    struct gcide_result *res;
    struct match_closure clos;

    clos.list = gcide_create_result_list(1);
    if (!clos.list)
	return NULL;

    if (dico_key_init(&clos.key, strat, word)) {
	dico_log(L_ERR, 0, _("gcide_match_all: key initialization failed"));
	dico_list_destroy(&clos.list);
	return NULL;
    }

    clos.strat = strat;
    gcide_idx_enumerate(db->idx, match_key, &clos);

    dico_key_deinit(&clos.key);

    if (dico_list_count(clos.list) == 0) {
	dico_list_destroy(&clos.list);
	return NULL;
    }

    res = calloc(1, sizeof(*res));
    if (!res) {
	dico_log(L_ERR, errno, "gcide_match_all");
	dico_list_destroy(&clos.list);
    } else {
	res->type = result_match;
	res->db = db;
	res->list = clos.list;
	res->compare_count = gcide_idx_defs(db->idx);
    }

    return (dico_result_t) res;
}
