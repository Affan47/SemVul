completion_get_aliases(const char *alias, char cmdchar)
{
	CONFIG_NODE *node;
	GList *complist;
	GSList *tmp;
	char *word;
	int len;

	g_return_val_if_fail(alias != NULL, NULL);


	node = iconfig_node_traverse("aliases", FALSE);
	tmp = node == NULL ? NULL : config_node_first(node->value);

	len = strlen(alias);
	complist = NULL;
	for (; tmp != NULL; tmp = config_node_next(tmp)) {
		CONFIG_NODE *node = tmp->data;

		if (node->type != NODE_TYPE_KEY)
			continue;

		if (g_strncasecmp(node->key, alias, len) == 0) {
			word = g_strdup_printf("%c%s", cmdchar, node->key);


			if (glist_find_icase_string(complist, word) == NULL)
				complist = g_list_insert_sorted(complist, word, (GCompareFunc) g_istr_cmp);
			else
				g_free(word);
		}
	}
	return complist;
}
