folder_read_list(void)
{
	GNode *node, *cur;
	XMLNode *xmlnode;
	gchar *path;

	path = folder_get_list_path();
	if (!is_file_exist(path)) return -1;
	node = xml_parse_file(path);
	if (!node) return -1;

	xmlnode = node->data;
	if (strcmp2(xmlnode->tag->tag, "folderlist") != 0) {
		g_warning("wrong folder list\n");
		xml_free_tree(node);
		return -1;
	}

	cur = node->children;
	while (cur != NULL) {
		Folder *folder;

		folder = folder_get_from_xml(cur);
		if (folder != NULL)
			folder_add(folder);
		else
			folder_unloaded_list = g_slist_append(folder_unloaded_list,
				(gpointer) xml_copy_tree(cur));
		cur = cur->next;
	}

	xml_free_tree(node);
	if (folder_list || folder_unloaded_list)
		return 0;
	else
		return -1;
}
