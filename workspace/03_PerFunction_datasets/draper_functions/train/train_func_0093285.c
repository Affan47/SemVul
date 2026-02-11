glade_gtk_list_item_post_create (GladeWidgetAdaptor *adaptor,
				 GObject            *object,
				 GladeCreateReason   reason)
{
	GtkWidget *label;

	g_return_if_fail (GTK_IS_LIST_ITEM (object));

	label = gtk_label_new ("");
	gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.5);
	gtk_misc_set_padding (GTK_MISC (label), 0, 1);

	gtk_container_add (GTK_CONTAINER (object), label);
	gtk_widget_show (label);
}
