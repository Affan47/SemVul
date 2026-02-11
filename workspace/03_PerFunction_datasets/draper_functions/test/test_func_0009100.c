label_pack(GtkWidget *table, const gchar *text, gint x, gint y, gboolean left)
{
	GtkWidget	*algn, *lab;

	algn = gtk_alignment_new(left ? 0.0f : 0.9f, 0.0f, 0.0f, 0.0f);
	lab  = gtk_label_new(text);
	if(left)
		gtk_label_set_justify(GTK_LABEL(lab), GTK_JUSTIFY_LEFT);
	gtk_container_add(GTK_CONTAINER(algn), lab);
	gtk_table_attach(GTK_TABLE(table), algn, x, x + 1, y, y + 1, GTK_FILL,0,4,0);
	return lab;
}
