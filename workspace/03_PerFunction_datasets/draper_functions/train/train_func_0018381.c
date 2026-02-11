ario_header_new (void)
{
        ARIO_LOG_FUNCTION_START;
        ArioHeader *header;
        ArioServer *server = ario_server_get_instance ();

        header = ARIO_HEADER (g_object_new (TYPE_ARIO_HEADER,
                                            NULL));

        g_return_val_if_fail (header->priv != NULL, NULL);


        g_signal_connect_object (server,
                                 "song_changed", G_CALLBACK (ario_header_song_changed_cb),
                                 header, 0);
        g_signal_connect_object (server,
                                 "album_changed", G_CALLBACK (ario_header_album_changed_cb),
                                 header, 0);
        g_signal_connect_object (server,
                                 "state_changed", G_CALLBACK (ario_header_state_changed_cb),
                                 header, 0);
        g_signal_connect_object (server,
                                 "elapsed_changed", G_CALLBACK (ario_header_elapsed_changed_cb),
                                 header, 0);
        g_signal_connect_object (server,
                                 "random_changed", G_CALLBACK (ario_header_random_changed_cb),
                                 header, 0);
        g_signal_connect_object (server,
                                 "repeat_changed", G_CALLBACK (ario_header_repeat_changed_cb),
                                 header, 0);

        return GTK_WIDGET (header);
}
