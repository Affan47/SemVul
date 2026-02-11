ario_playlist_drag_drop_cb (GtkWidget * widget,
                            gint x, gint y,
                            guint time,
                            ArioPlaylist *playlist)
{
        ARIO_LOG_FUNCTION_START;


        if (instance->priv->in_search)
                g_signal_stop_emission_by_name (widget, "drag_drop");

        return FALSE;
}
