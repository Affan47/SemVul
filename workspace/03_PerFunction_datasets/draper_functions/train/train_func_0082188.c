main_quit(void)
{
    g_log(LOG_DOMAIN, G_LOG_LEVEL_DEBUG, "Quiting gmpc....");


    pl3_hide();


    if (autoconnect_timeout)
        g_source_remove(autoconnect_timeout);


    mpd_signal_connect_connection_changed(connection, NULL, NULL);


    if (mpd_check_connected(connection))
    {
        if (cfg_get_single_value_as_int_with_default(config,
    				"connection", "stop-on-exit", FALSE))
        {
            mpd_player_stop(connection);
        }
        mpd_disconnect(connection);
    }


    gtk_main_quit();
}
