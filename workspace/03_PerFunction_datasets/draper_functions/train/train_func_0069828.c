defpref_selection(GtkTreeSelection *treeselection, gpointer user_data)
{
struct defpref_data *data;
GtkWidget *notebook;
GtkTreeView *treeview;
GtkTreeModel *model;
GtkTreeIter iter;

GValue        val = { 0, };
gint page;

	DB( g_print("\n[ui-pref] selection\n") );

	if (gtk_tree_selection_get_selected(treeselection, &model, &iter))
	{
		notebook = GTK_WIDGET(user_data);
		treeview = gtk_tree_selection_get_tree_view(treeselection);
		data = g_object_get_data(G_OBJECT(gtk_widget_get_ancestor(GTK_WIDGET(treeview), GTK_TYPE_WINDOW)), "inst_data");


		gtk_tree_model_get_value(model, &iter, LST_PREF_PAGE, &val);
		page = g_value_get_int (&val);
		DB( g_print(" - active is %d\n", page) );
		g_value_unset (&val);


		gtk_tree_model_get_value(model, &iter, LST_PREF_NAME, &val);
		gtk_label_set_text (GTK_LABEL (data->label), g_value_get_string (&val));
		g_value_unset (&val);

		gtk_tree_model_get_value(model, &iter, LST_PREF_ICON, &val);
		gtk_image_set_from_pixbuf (GTK_IMAGE (data->image),
                             g_value_get_object (&val));
		g_value_unset (&val);


		gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook), page);


	}

}
