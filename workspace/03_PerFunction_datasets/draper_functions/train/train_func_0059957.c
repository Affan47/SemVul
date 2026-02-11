release_node(struct gcov_node *node)
{
	list_del(&node->list);
	list_del(&node->all);
	debugfs_remove(node->dentry);
	remove_links(node);
	kfree(node->loaded_info);
	if (node->unloaded_info)
		gcov_info_free(node->unloaded_info);
	kfree(node);
}
