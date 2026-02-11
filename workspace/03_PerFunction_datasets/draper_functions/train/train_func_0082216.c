remove_info(struct gcov_node *node, struct gcov_info *info)
{
	int i;

	i = get_info_index(node, info);
	if (i < 0) {
		pr_warn("could not remove '%s' (not found)\n",
			gcov_info_filename(info));
		return;
	}
	if (gcov_persist)
		save_info(node, info);

	node->loaded_info[i] = node->loaded_info[node->num_loaded - 1];
	node->num_loaded--;
	if (node->num_loaded > 0)
		return;

	kfree(node->loaded_info);
	node->loaded_info = NULL;
	node->num_loaded = 0;
	if (!node->unloaded_info)
		remove_node(node);
}
