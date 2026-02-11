simo_combo_box_set_active_iter( SimoComboBox *combo_box,
                                     GtkTreeIter *iter )
{
  SimoComboBoxPrivate *mthis = combo_box->priv;
  GValue value = {0};
  gchar *text = 0;

  if( mthis->current_path )
    gtk_tree_path_free( mthis->current_path );

  mthis->current_path = gtk_tree_model_get_path( combo_box->model, iter );
  if( mthis->current_path )
    gtk_tree_model_get_value( combo_box->model, iter, combo_box->visible_column, &value );

  if( G_IS_VALUE( &value ) )
    text = get_gvalue_as_string( &value );
  if( text ){

    gtk_entry_set_text( GTK_ENTRY( combo_box->entry ), text );
    gtk_label_set_text( GTK_LABEL( combo_box->label ), text );


    g_free( text );
  }
  else{
    gtk_entry_set_text( GTK_ENTRY( combo_box->entry ), "" );
    gtk_label_set_text( GTK_LABEL( combo_box->label ), "" );

  }
  g_value_unset( &value );
}
