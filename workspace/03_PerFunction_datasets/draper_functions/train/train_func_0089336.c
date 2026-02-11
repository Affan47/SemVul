ast_loader_unregister(int (*v)(void))
{
	struct loadupdate *cur;

	AST_LIST_LOCK(&updaters);
	AST_LIST_TRAVERSE_SAFE_BEGIN(&updaters, cur, entry) {
		if (cur->updater == v)	{
			AST_LIST_REMOVE_CURRENT(entry);
			break;
		}
	}
	AST_LIST_TRAVERSE_SAFE_END;
	AST_LIST_UNLOCK(&updaters);

	return cur ? 0 : -1;
}
