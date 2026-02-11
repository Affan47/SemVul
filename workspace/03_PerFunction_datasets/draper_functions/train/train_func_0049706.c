geturl( FileAccessWindow* faw )
{
    gchar* url = NULL;
    const gchar* host;
    const gchar* database;
    const gchar* username;
    const gchar* password;
    const gchar* type;
    const gchar* file;
    const gchar* path;

    host = gtk_entry_get_text( faw->tf_host );
    database = gtk_entry_get_text( faw->tf_database );
    username = gtk_entry_get_text( faw->tf_username );
    password = gtk_entry_get_text( faw->tf_password );
    file = gtk_file_chooser_get_filename( faw->fileChooser );

    type = gtk_combo_box_text_get_active_text(faw->cb_uri_type );
    if ( gnc_uri_is_file_protocol( type ) )
    {
        if ( file == NULL )
            return NULL;
        else
            path = file;
    }
    else
        path = database;

    url = gnc_uri_create_uri (type, host, 0, username, password, path);

    return url;
}
