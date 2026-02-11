simo_combo_box_set_model( SimoComboBox *combo_box, GtkTreeModel *model)
{
  if( combo_box->model )
    g_object_unref( combo_box->model );

  combo_box->model = model;

  gtk_tree_view_set_model( combo_box->treeview, combo_box->model );
  if( combo_box->model ){
    g_object_ref( combo_box->model );
    g_signal_connect( combo_box->model, "row-deleted", G_CALLBACK( simo_combo_box_row_deleted ), combo_box );
    gtk_entry_set_completion( GTK_ENTRY( combo_box->entry ), NULL );

    combo_box->priv->completion = gtk_entry_completion_new();

    gtk_entry_set_completion( GTK_ENTRY( combo_box->entry ), combo_box->priv->completion );
    g_object_unref( combo_box->priv->completion );
    gtk_entry_completion_set_model( combo_box->priv->completion, combo_box->model );

  }


}
