add_custom_template_items(void)
{
	GSList *list = utils_get_config_files(GEANY_TEMPLATES_SUBDIR G_DIR_SEPARATOR_S "files");
	GSList *node;

	foreach_slist(node, list)
	{
		gchar *fname = node->data;

		add_file_item(fname, new_with_template_menu);
		g_free(fname);
	}
	g_slist_free(list);
	return list != NULL;
}
