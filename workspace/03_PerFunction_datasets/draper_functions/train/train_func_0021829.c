compute_public_data (GdaSet *set)
{
	GSList *list;
	GdaSetNode *node;
	GdaSetSource *source;
	GdaSetGroup *group;
	GHashTable *groups = NULL;


	while (set->nodes_list)
		set_remove_node (set, GDA_SET_NODE (set->nodes_list->data));
	while (set->sources_list)
		set_remove_source (set, GDA_SET_SOURCE (set->sources_list->data));

	g_slist_foreach (set->groups_list, (GFunc) group_free, NULL);
	g_slist_free (set->groups_list);
	set->groups_list = NULL;


	for (list = set->holders; list; list = list->next) {
		GdaHolder *holder = GDA_HOLDER (list->data);
		gint col;
		node = gda_set_node_new (holder);
		gda_set_node_set_data_model (node, gda_holder_get_source_model (holder, &col));
		gda_set_node_set_source_column (node, col);
		set->nodes_list = g_slist_prepend (set->nodes_list, node);
	}
	set->nodes_list = g_slist_reverse (set->nodes_list);


	for (list = set->nodes_list; list;list = list->next) {
		node = GDA_SET_NODE (list->data);


		source = NULL;
		if (gda_set_node_get_data_model (node)) {
			source = gda_set_get_source_for_model (set, gda_set_node_get_data_model (node));
			if (source)
				gda_set_source_add_node (source, node);
			else {
				source = gda_set_source_new (gda_set_node_get_data_model (node));
				gda_set_source_add_node (source, node);
				set->sources_list = g_slist_prepend (set->sources_list, source);
			}
		}


		group = NULL;
		if (gda_set_node_get_data_model (node) && groups)
			group = g_hash_table_lookup (groups, gda_set_node_get_data_model (node));
		if (group)
			gda_set_group_add_node (group, node);
		else {
			group = gda_set_group_new (node);
			gda_set_group_set_source (group, source);
			set->groups_list = g_slist_prepend (set->groups_list, group);
			if (gda_set_node_get_data_model (node)) {
				if (!groups)
					groups = g_hash_table_new (NULL, NULL);

				g_hash_table_insert (groups, gda_set_node_get_data_model (node), group);
			}
		}
	}
	set->groups_list = g_slist_reverse (set->groups_list);
	if (groups)
		g_hash_table_destroy (groups);

#ifdef GDA_DEBUG_signal
        g_print (">> 'PUBLIC_DATA_CHANGED' from %p\n", set);
#endif
	g_signal_emit (set, gda_set_signals[PUBLIC_DATA_CHANGED], 0);
#ifdef GDA_DEBUG_signal
        g_print ("<< 'PUBLIC_DATA_CHANGED' from %p\n", set);
#endif
}
