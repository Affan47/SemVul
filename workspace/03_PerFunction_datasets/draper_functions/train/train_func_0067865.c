brasero_file_node_sort_name_cb (gconstpointer obj_a, gconstpointer obj_b)
{
	gint res;
	const BraseroFileNode *a = obj_a;
	const BraseroFileNode *b = obj_b;


	res = brasero_file_node_sort_default_cb (a, b);
	if (res)
		return res;

	return strcmp (BRASERO_FILE_NODE_NAME (a), BRASERO_FILE_NODE_NAME (b));
}
