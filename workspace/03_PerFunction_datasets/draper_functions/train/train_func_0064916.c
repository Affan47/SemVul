svn_cat_command_finalize (GObject *object)
{
	SvnCatCommand *self;
	GList *current_output;

	self = SVN_CAT_COMMAND (object);

	g_free (self->priv->path);

	current_output = self->priv->output->head;

	while (current_output)
	{
		g_free (current_output->data);
		current_output = g_list_next (current_output);
	}

	g_queue_free (self->priv->output);

	g_free (self->priv);

	G_OBJECT_CLASS (svn_cat_command_parent_class)->finalize (object);
}
