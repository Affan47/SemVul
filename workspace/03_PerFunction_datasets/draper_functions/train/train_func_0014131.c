foreach_node_move (AnjutaProjectNode *g_node, gpointer data)
{
	AmpProject *project = ((AmpMovePacket *)data)->project;
	GFile *old_root_file = ((AmpMovePacket *)data)->old_root_file;
	GFile *new_root_file = ((AmpMovePacket *)data)->new_root_file;
	gchar *relative;
	GFile *new_file;

	switch (anjuta_project_node_get_node_type (g_node))
	{
	case ANJUTA_PROJECT_GROUP:
		relative = get_relative_path (old_root_file, anjuta_project_node_get_file (g_node));
		new_file = g_file_resolve_relative_path (new_root_file, relative);
		g_free (relative);
		amp_group_node_set_file (AMP_GROUP_NODE (g_node), new_file);
		g_object_unref (new_file);

		g_hash_table_insert (project->groups, g_file_get_uri (new_file), g_node);
		break;
	case ANJUTA_PROJECT_SOURCE:
		relative = get_relative_path (old_root_file, anjuta_project_node_get_file (g_node));
		new_file = g_file_resolve_relative_path (new_root_file, relative);
		g_free (relative);
		amp_source_node_set_file (AMP_SOURCE_NODE (g_node), new_file);
		g_object_unref (new_file);
		break;
	default:
		break;
	}
}
