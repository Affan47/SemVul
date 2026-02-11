revision_info_action_connect_proxy (GtkAction *action,
				    GtkWidget *widget)
{
	GiggleRevisionInfoActionPriv *priv = GET_PRIV (action);
	GtkWidget                    *child;
	GParamSpec                   *pspec;

	GTK_ACTION_CLASS (giggle_revision_info_action_parent_class)->connect_proxy (action, widget);

	if (GTK_IS_TOOL_ITEM (widget)) {
		child = gtk_bin_get_child (GTK_BIN (widget));
		child = gtk_bin_get_child (GTK_BIN (child));

		gtk_tool_item_set_expand (GTK_TOOL_ITEM (widget), priv->expand);
		g_signal_connect (action, "notify", G_CALLBACK (notify_cb), child);

		pspec = g_object_class_find_property (G_OBJECT_GET_CLASS (action), "revision");
		notify_cb (action, pspec, child);

		pspec = g_object_class_find_property (G_OBJECT_GET_CLASS (action), "label");
		notify_cb (action, pspec, child);
	}
}
