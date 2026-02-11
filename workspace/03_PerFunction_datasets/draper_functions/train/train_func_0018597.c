ui_cat_manage_dialog_move(GtkWidget *widget, gpointer user_data)
{
struct ui_cat_manage_dialog_data *data;
GtkWidget *window, *content, *mainvbox, *getwidget;
GtkTreeSelection *selection;
GtkTreeModel		 *model;
GtkTreeIter			 iter;

	data = g_object_get_data(G_OBJECT(gtk_widget_get_ancestor(widget, GTK_TYPE_WINDOW)), "inst_data");
	DB( g_print("(defcategory) move\n") );

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(data->LV_cat));

	if (gtk_tree_selection_get_selected(selection, &model, &iter))
	{
	Category *item;

		gtk_tree_model_get(model, &iter, LST_DEFCAT_DATAS, &item, -1);

		window = gtk_dialog_new_with_buttons (_("Move to..."),
						    GTK_WINDOW (data->window),
						    0,
						    GTK_STOCK_CANCEL,
						    GTK_RESPONSE_REJECT,
						    GTK_STOCK_OK,
						    GTK_RESPONSE_ACCEPT,
						    NULL);

		content = gtk_dialog_get_content_area(GTK_DIALOG (window));
		mainvbox = gtk_vbox_new (FALSE, 0);
		gtk_box_pack_start (GTK_BOX (content), mainvbox, TRUE, TRUE, 0);
		gtk_container_set_border_width (GTK_CONTAINER (mainvbox), HB_BOX_SPACING);

		getwidget = ui_cat_comboboxentry_new(NULL);
		gtk_box_pack_start (GTK_BOX (mainvbox), getwidget, TRUE, TRUE, 0);

		gtk_dialog_set_response_sensitive(GTK_DIALOG(window), GTK_RESPONSE_ACCEPT, FALSE);

		gtk_widget_show_all(mainvbox);

		g_signal_connect (G_OBJECT (getwidget), "changed", G_CALLBACK (ui_cat_manage_dialog_move_entry_cb), window);

		ui_cat_comboboxentry_populate_except(GTK_COMBO_BOX(getwidget), GLOBALS->h_cat, item->key);
		gtk_widget_grab_focus (getwidget);


		gint result = gtk_dialog_run (GTK_DIALOG (window));

		if(result == GTK_RESPONSE_ACCEPT)
		{
		gboolean result;
		gchar *npn;

			npn = ui_cat_comboboxentry_get_name(GTK_COMBO_BOX(getwidget)),

			result = ui_dialog_msg_question(
				GTK_WINDOW(window),
				_("Move this category to another one ?"),
				_("This will replace '%s' by '%s',\n"
				  "and then remove '%s'"),
				item->name,
				npn,
				item->name,
				NULL
				);

			if( result == GTK_RESPONSE_YES )
			{
			Category *newcat, *parent;
			guint dstkey;

				dstkey = ui_cat_comboboxentry_get_key_add_new(GTK_COMBO_BOX(getwidget));
				newcat = da_cat_get (dstkey);

				DB( g_print(" moving to %d\n", dstkey) );

				category_move(item->key, dstkey);


				parent = da_cat_get(item->parent);
				if(parent != NULL && (parent->flags & GF_INCOME))
					newcat->flags |= GF_INCOME;


				da_cat_remove(item->key);
				ui_cat_listview_remove_selected(GTK_TREE_VIEW(data->LV_cat));


				ui_cat_listview_add(GTK_TREE_VIEW(data->LV_cat), newcat, NULL);

				data->change++;
			}
	    }


		gtk_widget_destroy (window);
	}

}
