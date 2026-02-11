ast_cdr_free_vars(struct ast_cdr *cdr, int recur)
{


	for (; cdr; cdr = recur ? cdr->next : NULL) {
		struct ast_var_t *vardata;
		struct varshead *headp = &cdr->varshead;
		while ((vardata = AST_LIST_REMOVE_HEAD(headp, entries)))
			ast_var_delete(vardata);
	}
}
