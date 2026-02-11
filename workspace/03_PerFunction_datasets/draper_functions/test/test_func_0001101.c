gsb_bank_create_combobox ( gint index,
                        GCallback hook,
                        gpointer data,
                        GCallback default_func,
                        gint number_for_func )
{
    GtkWidget *combo_box;
    GtkCellRenderer *renderer;


    if (!bank_list_model)
	gsb_bank_update_selected_line_model (NULL);

    combo_box = gtk_combo_box_new_with_model (bank_list_model);


    renderer = gtk_cell_renderer_text_new ();
    gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (combo_box), renderer, TRUE);
    gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (combo_box), renderer,
				    "text", 0,
				    NULL);


    gtk_combo_box_set_row_separator_func ( GTK_COMBO_BOX (combo_box),
					   (GtkTreeViewRowSeparatorFunc) gsb_bank_list_check_separator,
					   NULL, NULL );


    g_signal_connect ( G_OBJECT (combo_box),
		       "changed",
		       G_CALLBACK (gsb_bank_list_changed),
		       NULL );


    g_object_set_data ( G_OBJECT (combo_box),
			"number_for_func", GINT_TO_POINTER (number_for_func));
    if (default_func)
	g_object_set_data ( G_OBJECT (combo_box), "changed",
			    (gpointer) g_signal_connect_after (G_OBJECT(combo_box), "changed",
							       G_CALLBACK (gsb_bank_combobox_changed), default_func ));

    if ( hook )
	g_object_set_data ( G_OBJECT (combo_box), "changed-hook",
			    (gpointer) g_signal_connect_after (G_OBJECT(combo_box), "changed",
							       ((GCallback) hook), data ));


    gsb_bank_list_set_bank (combo_box, index, number_for_func);
    return combo_box;
}
