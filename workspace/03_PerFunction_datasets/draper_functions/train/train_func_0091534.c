object_finalize (GObject *gobject)
{
	SeahorseWidget *swidget;

	swidget = SEAHORSE_WIDGET (gobject);


    if (widgets) {
    	g_hash_table_remove (widgets, swidget->name);
    	if (g_hash_table_size (widgets) == 0) {
    		g_hash_table_destroy (widgets);
    		widgets = NULL;
    	}
    }

	g_signal_handlers_disconnect_by_func (SCTX_APP (), context_destroyed, swidget);
    if (seahorse_widget_get_widget (swidget, swidget->name))
        gtk_widget_destroy (GTK_WIDGET (seahorse_widget_get_widget (swidget, swidget->name)));

	g_object_unref (swidget->gtkbuilder);
	swidget->gtkbuilder = NULL;

	g_free (swidget->name);

	G_OBJECT_CLASS (parent_class)->finalize (gobject);
}
