ui_bud_manage_selection_change(GtkWidget *treeview, gpointer user_data)
{
struct ui_bud_manage_data *data;
GtkTreeModel *model;
GtkTreeIter iter;

	data = g_object_get_data(G_OBJECT(gtk_widget_get_ancestor(GTK_WIDGET(treeview), GTK_TYPE_WINDOW)), "inst_data");

	DB( g_print("(ui_bud_manage) changed\n") );

	data->cat = NULL;

	if(gtk_tree_selection_get_selected(gtk_tree_view_get_selection(GTK_TREE_VIEW(data->LV_cat)), &model, &iter))
	{
	Category *item;

		gtk_tree_model_get(GTK_TREE_MODEL(model), &iter,
			LST_DEFCAT_DATAS, &item,
			-1);

		DB( g_print(" selected %s\n", item->name) );

		if(data->lastcatitem != NULL && item != data->lastcatitem)
		{
			DB( g_print(" -> should do a get for last selected (%s)\n", data->lastcatitem->name) );
			ui_bud_manage_getlast(data);
		}


		data->cat = item;
		data->lastcatitem = item;

		ui_bud_manage_set(treeview, NULL);
	}
	else
	{
		data->lastcatitem = NULL;
	}

	ui_bud_manage_update(treeview, NULL);

}
