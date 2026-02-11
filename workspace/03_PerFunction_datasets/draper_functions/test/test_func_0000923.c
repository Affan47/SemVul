menu_item_selected_cb (GtkWidget *item, GladeWindow *window)
{
	GtkAction *action;
	gchar *tooltip;

	action = gtk_activatable_get_related_action (GTK_ACTIVATABLE (item));
	g_object_get (G_OBJECT (action), "tooltip", &tooltip, NULL);

	if (tooltip != NULL)
		gtk_statusbar_push (GTK_STATUSBAR (window->priv->statusbar),
				    window->priv->statusbar_menu_context_id, tooltip);

	g_free (tooltip);
}
