ario_shell_cmd_cover_select (GtkAction *action,
                             ArioShell *shell)
{
        ARIO_LOG_FUNCTION_START;
        GtkWidget *coverselect;
        ArioServerAlbum server_album;


        server_album.artist = ario_server_get_current_artist ();
        server_album.album = ario_server_get_current_album ();
        server_album.path = g_path_get_dirname ((ario_server_get_current_song ())->file);

        if (!server_album.album)
                server_album.album = ARIO_SERVER_UNKNOWN;

        if (!server_album.artist)
                server_album.artist = ARIO_SERVER_UNKNOWN;

        coverselect = ario_shell_coverselect_new (&server_album);
        gtk_dialog_run (GTK_DIALOG (coverselect));
        gtk_widget_destroy (coverselect);
        g_free (server_album.path);
}
