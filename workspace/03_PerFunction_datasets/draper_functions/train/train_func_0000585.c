cb_uri_type_changed_cb( GtkComboBoxText* cb )
{
    GtkWidget* dialog;
    FileAccessWindow* faw;
    const gchar* type;

    g_return_if_fail( cb != NULL );

    dialog = gtk_widget_get_toplevel( GTK_WIDGET(cb) );
    g_return_if_fail( dialog != NULL );
    faw = g_object_get_data( G_OBJECT(dialog), "FileAccessWindow" );
    g_return_if_fail( faw != NULL );

    type = gtk_combo_box_text_get_active_text( cb );
    set_widget_sensitivity_for_uri_type( faw, type );
}
