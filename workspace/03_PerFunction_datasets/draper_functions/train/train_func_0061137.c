pat_prune_ptr(struct pattern_expr *expr)
{
	struct pattern_list *pat, *tmp;

	list_for_each_entry_safe(pat, tmp, &expr->patterns, list) {
		free(pat->pat.ptr.ptr);
		free(pat->pat.smp);
		free(pat);
	}

	free_pattern_tree(&expr->pattern_tree);
	free_pattern_tree(&expr->pattern_tree_2);
	LIST_INIT(&expr->patterns);
}
