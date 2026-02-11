gsb_fyear_config_select ( GtkTreeSelection *tree_selection,
				   gpointer null )
{
    GtkTreeModel *model;
    GtkTreeIter iter;
    gint fyear_number;
    GtkWidget *tree_view;
    GtkWidget *widget;

    if (!gtk_tree_selection_get_selected ( GTK_TREE_SELECTION (tree_selection),
					   &model,
					   &iter ))
	return FALSE;

    gtk_tree_model_get ( GTK_TREE_MODEL (model),
			 &iter,
			 FYEAR_NUMBER_COLUMN, &fyear_number,
			 -1 );

    tree_view = GTK_WIDGET (gtk_tree_selection_get_tree_view (tree_selection));


    widget = g_object_get_data ( G_OBJECT (model),
				 "fyear_name_entry" );
    gsb_autofunc_entry_set_value ( widget,
				   gsb_data_fyear_get_name (fyear_number),
				   fyear_number );


    widget = g_object_get_data ( G_OBJECT (model),
				 "fyear_begin_date_entry" );
    gsb_calendar_entry_set_color (widget, TRUE);
    gsb_autofunc_date_set ( widget,
			    gsb_data_fyear_get_beginning_date (fyear_number),
			    fyear_number );


    widget = g_object_get_data ( G_OBJECT (model),
				 "fyear_end_date_entry" );
    gsb_calendar_entry_set_color (widget, TRUE);
    gsb_autofunc_date_set ( widget,
			    gsb_data_fyear_get_end_date (fyear_number),
			    fyear_number );


    widget = g_object_get_data ( G_OBJECT (model),
				 "fyear_show_button" );
    gsb_autofunc_checkbutton_set_value ( widget,
					 gsb_data_fyear_get_form_show (fyear_number),
					 fyear_number );


    widget = g_object_get_data ( G_OBJECT (model),
				 "invalid_label" );
    if (gsb_data_fyear_get_invalid (fyear_number))
    {
	gtk_label_set_markup ( GTK_LABEL (widget),
			       gsb_data_fyear_get_invalid_message (fyear_number));
	gtk_widget_show (widget);
    }
    else
	gtk_widget_hide (widget);


    gtk_widget_set_sensitive ( g_object_get_data ( G_OBJECT (model),
						   "paddingbox_details" ),
			       TRUE );
    gtk_widget_set_sensitive ( g_object_get_data ( G_OBJECT (model),
						   "remove_fyear_button" ),
			       TRUE );

    return FALSE;
}
