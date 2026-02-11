toplevel_update_tabs(toplevel_t * top)
{
	gint i = gtk_notebook_get_n_pages(top->notebook) - 1;
	while (i >= 0) {
		GtkWidget *child = gtk_notebook_get_nth_page(top->notebook, i);
		GtkWidget *tab = gtk_notebook_get_tab_label(top->notebook, child);
		GtkWidget *label = g_object_get_data(G_OBJECT(tab), "label");
		message_view_t *v = g_object_get_data(G_OBJECT(tab), "view-object");
		seaudit_model_t *model = message_view_get_model(v);
		const char *name = seaudit_model_get_name(model);
		gtk_label_set_text(GTK_LABEL(label), name);
		i--;
	}
}
