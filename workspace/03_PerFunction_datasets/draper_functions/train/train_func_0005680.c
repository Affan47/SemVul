audgui_infowin_show (int playlist, int entry)
{
    char * filename = aud_playlist_entry_get_filename (playlist, entry);
    g_return_if_fail (filename != NULL);

    PluginHandle * decoder = aud_playlist_entry_get_decoder (playlist, entry,
     FALSE);
    if (decoder == NULL)
        goto FREE;

    if (aud_custom_infowin (filename, decoder))
        goto FREE;

    Tuple * tuple = aud_playlist_entry_get_tuple (playlist, entry, FALSE);

    if (tuple == NULL)
    {
        char * message = g_strdup_printf (_("No info available for %s.\n"),
         filename);
        aud_interface_show_error (message);
        g_free (message);
        goto FREE;
    }

    infowin_show (playlist, entry, filename, tuple, decoder,
     aud_file_can_write_tuple (filename, decoder));
    tuple_unref (tuple);

FREE:
    str_unref (filename);
}
