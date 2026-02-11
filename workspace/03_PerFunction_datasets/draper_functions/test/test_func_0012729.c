queue_file_write(const char *filename)
{
	struct direntry *cur;

	AST_LIST_TRAVERSE_SAFE_BEGIN(&openlist, cur, list) {
		if (!strcmp(cur->name, filename)) {
			AST_LIST_REMOVE_CURRENT(list);
			ast_free(cur);
			queue_file(filename, 0);
			break;
		}
	}
	AST_LIST_TRAVERSE_SAFE_END
}
