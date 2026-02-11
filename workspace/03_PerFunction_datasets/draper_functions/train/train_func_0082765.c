can_redo (GeditDocument *doc,
	  GParamSpec    *pspec,
	  GeditWindow   *window)
{
	GtkAction *action;
	gboolean sensitive;

	sensitive = gtk_source_buffer_can_redo (GTK_SOURCE_BUFFER (doc));

	if (doc != gedit_window_get_active_document (window))
		return;

	action = gtk_action_group_get_action (window->priv->action_group,
					     "EditRedo");
	gtk_action_set_sensitive (action, sensitive);
}
