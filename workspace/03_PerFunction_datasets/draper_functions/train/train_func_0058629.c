gconf_tree_model_init (GConfTreeModel *model)
{
	Node *root;

	root = g_new0 (Node, 1);
	root->path = g_strdup ("/");
	root->offset = 0;

	model->root = root;
	model->client = gconf_client_get_default ();
}
