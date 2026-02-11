amp_project_save (AmpNode *root, AmpNode *parent, AmpProject *project, GError **error)
{
	AnjutaTokenFile *tfile;
	AnjutaProjectNode *child;


	tfile = AMP_PROJECT (root)->configure_file;
	if (anjuta_token_file_is_dirty (tfile))
	{
		if (!anjuta_token_file_save (tfile, error)) return FALSE;
	}

	if (!AMP_NODE_CLASS (parent_class)->save (root, parent, project, error))
	{
		return FALSE;
	}


	for (child = anjuta_project_node_first_child (ANJUTA_PROJECT_NODE (root)); child != NULL; child = anjuta_project_node_next_sibling (child))
	{
		if (!amp_node_save (AMP_NODE (child), root, project, error)) return FALSE;
	}

	return TRUE;
}
