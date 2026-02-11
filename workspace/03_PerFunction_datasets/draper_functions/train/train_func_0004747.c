__tree_print(int lvl, struct tree_node *root, struct string *str)
{
	if (!root)
		return str_append(str, "<null>");

	if (node_is_stmt(root))
		return print_stmt(lvl, root, str);

	return print_expr(lvl, root, str);
}
