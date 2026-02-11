ui_arc_manage_update(GtkWidget *widget, gpointer user_data)
{
struct ui_arc_manage_data *data;
GtkTreeModel		 *model;
GtkTreeIter			 iter;
gboolean selected, sensitive;
Archive *arcitem;


	DB( g_print("(defarchive) update\n") );

	data = g_object_get_data(G_OBJECT(gtk_widget_get_ancestor(widget, GTK_TYPE_WINDOW)), "inst_data");


	selected = gtk_tree_selection_get_selected(gtk_tree_view_get_selection(GTK_TREE_VIEW(data->LV_arc)), &model, &iter);

	DB( g_print(" selected = %d\n", selected) );

	sensitive = (selected == TRUE) ? TRUE : FALSE;
	gtk_widget_set_sensitive(data->PO_pay, sensitive);
	gtk_widget_set_sensitive(data->ST_word, sensitive);
	gtk_widget_set_sensitive(data->ST_amount, sensitive);
	gtk_widget_set_sensitive(data->BT_amount, sensitive);


	gtk_widget_set_sensitive(data->CM_valid, sensitive);
	gtk_widget_set_sensitive(data->CM_remind, sensitive);

	gtk_widget_set_sensitive(data->CM_cheque, sensitive);

	gtk_widget_set_sensitive(data->NU_mode, sensitive);
	gtk_widget_set_sensitive(data->PO_grp, sensitive);
	gtk_widget_set_sensitive(data->PO_acc, sensitive);
	gtk_widget_set_sensitive(data->PO_accto, sensitive);

	gtk_widget_set_sensitive(data->CM_auto, sensitive);

	gtk_widget_set_sensitive(data->BT_rem, sensitive);


	if(selected)
	{
		gtk_tree_model_get(model, &iter, LST_DEFARC_DATAS, &arcitem, -1);

		if(data->lastarcitem != NULL && arcitem != data->lastarcitem)
		{
			DB( g_print(" -> should do a get for last selected (%s)\n", data->lastarcitem->wording) );
			ui_arc_manage_getlast(data);
		}
		data->lastarcitem = arcitem;


		ui_arc_manage_set(widget, NULL);

	}
	else
	{
		data->lastarcitem = NULL;

	}

	ui_arc_manage_scheduled(widget, NULL);
	ui_arc_manage_paymode(widget,NULL);


}
