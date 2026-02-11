precache_transactions(struct dundi_request *dr, struct dundi_mapping *maps, int mapcount, int *expiration, int *foundanswers)
{
	struct dundi_transaction *trans;


	AST_LIST_LOCK(&peers);
	AST_LIST_TRAVERSE(&dr->trans, trans, parentlist) {
		if (trans->thread)
			ast_log(LOG_WARNING, "This shouldn't happen, really...\n");
		trans->thread = 1;
	}
	AST_LIST_UNLOCK(&peers);

	AST_LIST_TRAVERSE(&dr->trans, trans, parentlist) {
		if (!ast_test_flag(trans, FLAG_DEAD))
			precache_trans(trans, maps, mapcount, expiration, foundanswers);
	}


	AST_LIST_LOCK(&peers);
	AST_LIST_TRAVERSE_SAFE_BEGIN(&dr->trans, trans, parentlist) {
		trans->thread = 0;
		if (ast_test_flag(trans, FLAG_DEAD)) {
			ast_debug(1, "Our transaction went away!\n");


			destroy_trans(trans, 0);
		}
	}
	AST_LIST_TRAVERSE_SAFE_END
	AST_LIST_UNLOCK(&peers);

	return 0;
}
