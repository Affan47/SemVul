folder_unregister_class(FolderClass *klass)
{
	GList *folderlist, *cur;

	debug_print("unregistering folder class %s\n", klass->idstr);

	class_list = g_slist_remove(class_list, klass);

	folderlist = g_list_copy(folder_get_list());
	for (cur = folderlist; cur != NULL; cur = g_list_next(cur)) {
		Folder *folder = (Folder *) cur->data;

		if (folder->klass == klass) {
			GNode *xmlnode = folder_get_xml_node(folder);
			folder_unloaded_list = g_slist_append(folder_unloaded_list, xmlnode);
			folder_destroy(folder);
		}
	}
	g_list_free(folderlist);
}
