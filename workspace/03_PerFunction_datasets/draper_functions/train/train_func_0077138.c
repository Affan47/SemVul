breaks_get_for_document(const char* file)
{
	GList *breaks = NULL;
	GTree *tree = g_hash_table_lookup(files, file);
	if (tree)
	{
		g_tree_foreach(tree, tree_foreach_add_to_list, &breaks);
	}
	return breaks;
}
