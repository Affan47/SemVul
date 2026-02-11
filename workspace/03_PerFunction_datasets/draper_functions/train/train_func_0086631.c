playlist3_source_drag_data_recieved(GtkWidget * widget,
GdkDragContext * context,
gint x,
gint y, GtkSelectionData * data, guint info, guint time_recieved)
{
    if (info != 99)
    {
        int found = 0;
        const gchar *url_data = (gchar *) data->data;
        int i;
        if (url_data)
        {

            gchar **url = g_uri_list_extract_uris(url_data);
            for (i = 0; url && url[i]; i++)
            {
                gchar *scheme = g_uri_parse_scheme(url[i]);

                if (scheme)
                {
            		gchar *fu = g_uri_unescape_string(url[i], NULL);
                    url_start_real(fu);
                    g_free(fu);
                    g_free(scheme);
                }
            }
            if (url)
                g_strfreev(url);
        }

        gtk_drag_finish(context, found, FALSE, time_recieved);
    } else
    {
        MpdData *mdata;
        gchar **stripped;
        int i;
        guchar *odata = gtk_selection_data_get_text(data);
        stripped = g_strsplit((gchar *) odata, "\n", 0);
        g_free(odata);
        if (context->action == GDK_ACTION_MOVE)
        {
            mpd_playlist_clear(connection);
        }
        mpd_database_search_start(connection, TRUE);
        for (i = 0; stripped && stripped[i]; i++)
        {
            gchar **request = g_strsplit(stripped[i], ":", 2);
            mpd_database_search_add_constraint(connection, mpd_misc_get_tag_by_name(request[0]), request[1]);
            g_strfreev(request);
        }
        mdata = mpd_database_search_commit(connection);
        for (; mdata; mdata = mpd_data_get_next(mdata))
        {
            mpd_playlist_queue_add(connection, mdata->song->file);
        }
        mpd_playlist_queue_commit(connection);
        if (context->action == GDK_ACTION_MOVE)
        {
            mpd_player_play(connection);
        }

        g_strfreev(stripped);
        gtk_drag_finish(context, TRUE, FALSE, time_recieved);
    }
}
