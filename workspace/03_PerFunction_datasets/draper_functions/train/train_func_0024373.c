brasero_data_project_reset (BraseroDataProject *self)
{
	BraseroDataProjectPrivate *priv;
	BraseroDataProjectClass *klass;
	guint num_nodes;

	priv = BRASERO_DATA_PROJECT_PRIVATE (self);


	num_nodes = brasero_file_node_get_n_children (priv->root);
	brasero_data_project_clear (self);

	klass = BRASERO_DATA_PROJECT_GET_CLASS (self);
	if (klass->reset)
		klass->reset (self, num_nodes);

	priv->loading = 0;
	priv->root = brasero_file_node_root_new ();
}
