hilight_remove_config(HILIGHT_REC *rec)
{
	CONFIG_NODE *node;

	g_return_if_fail(rec != NULL);

	node = iconfig_node_traverse("hilights", FALSE);
	if (node != NULL) iconfig_node_list_remove(node, g_slist_index(hilights, rec));
}
