gsb_fyear_config_modify_fyear ( GtkWidget *entry,
					 GtkWidget *tree_view)
{
    GtkTreeModel *model;
    GtkTreeIter iter;
    gint fyear_number;
    GtkWidget *widget;
    gchar *invalid;

    if (!gtk_tree_selection_get_selected ( GTK_TREE_SELECTION (gtk_tree_view_get_selection (GTK_TREE_VIEW (tree_view))),
					   &model,
					   &iter ))
	return FALSE;

    gtk_tree_model_get ( GTK_TREE_MODEL (model),
			 &iter,
			 FYEAR_NUMBER_COLUMN, &fyear_number,
			 -1 );


    if (!fyear_number)
	return FALSE;


    widget = g_object_get_data ( G_OBJECT (model),
				 "invalid_label" );


     gsb_fyear_update_invalid (tree_view);


     if (gsb_data_fyear_get_invalid (fyear_number))
     {

	 invalid = GTK_STOCK_DIALOG_WARNING;
	 gtk_label_set_markup ( GTK_LABEL (widget),
				gsb_data_fyear_get_invalid_message (fyear_number));
	 gtk_widget_show (widget);
     }
     else
     {
	 invalid = NULL;
	 gtk_widget_hide (widget);
     }

     gtk_list_store_set ( GTK_LIST_STORE (model),
			  &iter,
			  FYEAR_NAME_COLUMN, gsb_data_fyear_get_name (fyear_number),
			  FYEAR_BEGIN_DATE_COLUMN, gsb_format_gdate (gsb_data_fyear_get_beginning_date (fyear_number)),
			  FYEAR_END_DATE_COLUMN, gsb_format_gdate (gsb_data_fyear_get_end_date (fyear_number)) ,
			  FYEAR_INVALID_COLUMN, invalid,
			  FYEAR_NUMBER_COLUMN, fyear_number,
			  -1 );
     if ( etat.modification_fichier == 0 )
        modification_fichier ( TRUE );
     return FALSE;
}
