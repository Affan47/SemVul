amp_project_map_children (GHashTable *map, AnjutaProjectNode *old_node, AnjutaProjectNode *new_node)
{
	GList *children = NULL;

	if (new_node != NULL)
	{
		for (new_node = anjuta_project_node_first_child (new_node); new_node != NULL; new_node = anjuta_project_node_next_sibling (new_node))
		{
			children = g_list_prepend (children, new_node);
		}
		children = g_list_reverse (children);
	}

	for (old_node = anjuta_project_node_first_child (old_node); old_node != NULL; old_node = anjuta_project_node_next_sibling (old_node))
	{
		GList *same;

		same = g_list_find_custom (children, old_node, (GCompareFunc)amp_project_compare_node);

		if (same != NULL)
		{

			g_hash_table_insert (map, (AnjutaProjectNode *)same->data, old_node);

			amp_project_map_children (map, old_node, (AnjutaProjectNode *)same->data);
			children = g_list_delete_link (children, same);
		}
		else
		{


			g_hash_table_insert (map, old_node, NULL);
		}
	}


	for (; children != NULL; children = g_list_delete_link (children,  children))
	{


		g_hash_table_insert (map, children->data, children->data);
	}
}
