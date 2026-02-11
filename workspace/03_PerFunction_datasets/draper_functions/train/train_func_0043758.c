set_remove_node (GdaSet *set, GdaSetNode *node)
{
	g_return_if_fail (g_slist_find (set->nodes_list, node));
	gda_set_node_free (node);
	set->nodes_list = g_slist_remove (set->nodes_list, node);
}
