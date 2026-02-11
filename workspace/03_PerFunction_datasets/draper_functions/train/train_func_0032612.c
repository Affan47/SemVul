gda_set_get_group (GdaSet *set, GdaHolder *holder)
{
	GdaSetNode *node;
	GdaSetGroup *retval = NULL;
	GSList *list, *sublist;
	GdaHolder *node_holder;

	g_return_val_if_fail (GDA_IS_SET (set), NULL);
	g_return_val_if_fail (set->priv, NULL);
	g_return_val_if_fail (GDA_IS_HOLDER (holder), NULL);

	g_return_val_if_fail (g_slist_find (set->holders, holder), NULL);

	for (list = set->groups_list; list && !retval; list = list->next) {
		retval = GDA_SET_GROUP (list->data);
		sublist = gda_set_group_get_nodes (retval);
		while (sublist && !retval) {
			node = GDA_SET_NODE (sublist->data);
			if (node) {
				node_holder = gda_set_node_get_holder (node);
				if (node_holder == holder)
					break;
				else {
					sublist = g_slist_next (sublist);
					retval = NULL;
				}
			}
		}
	}
	return retval;
}
