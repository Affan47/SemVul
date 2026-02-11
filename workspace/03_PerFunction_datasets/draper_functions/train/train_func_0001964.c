amp_group_node_delete_token (AmpProject  *project, AmpGroupNode *group, GError **error)
{
	GList *item;
	AnjutaProjectNode *parent;


	parent =  anjuta_project_node_parent_type (ANJUTA_PROJECT_NODE (group), ANJUTA_PROJECT_GROUP);
	if (parent == NULL) return FALSE;

	for (item = amp_group_node_get_token (group, AM_GROUP_TOKEN_SUBDIRS); item != NULL; item = g_list_next (item))
	{
		AnjutaToken *token = (AnjutaToken *)item->data;
		AnjutaTokenStyle *style;
		AnjutaToken *list;

		list = anjuta_token_list (token);


		style = anjuta_token_style_new_from_base (project->am_space_list);
		anjuta_token_style_update (style, list);

		anjuta_token_remove_word (token);
		anjuta_token_style_format (style, list);
		anjuta_token_style_free (style);


		if (anjuta_token_first_word (list) == NULL)
		{
			anjuta_token_remove_list (anjuta_token_list (list));
		}

		amp_group_node_update_makefile (AMP_GROUP_NODE (parent), list);
	}


	for (item = amp_group_node_get_token (group, AM_GROUP_TOKEN_CONFIGURE); item != NULL; item = g_list_next (item))
	{
		AnjutaToken *token = (AnjutaToken *)item->data;
		AnjutaToken *args;
		AnjutaTokenStyle *style;

		args = anjuta_token_list (token);


		style = anjuta_token_style_new_from_base (project->ac_space_list);
		anjuta_token_style_update (style, args);

		anjuta_token_remove_word (token);

		anjuta_token_style_format (style, args);
		anjuta_token_style_free (style);

		amp_project_update_configure (project, args);
	}

	return TRUE;
}
