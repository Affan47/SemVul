ario_tooltip_sync_tooltip_song (ArioTooltip *tooltip)
{
        ARIO_LOG_FUNCTION_START;
        gchar *title;

        switch (ario_server_get_current_state ()) {
        case ARIO_STATE_PLAY:
        case ARIO_STATE_PAUSE:

                title = ario_util_format_title (ario_server_get_current_song ());
                gtk_label_set_text (GTK_LABEL (tooltip->priv->tooltip_primary),
                                    title);
                break;
        default:

                gtk_label_set_text (GTK_LABEL (tooltip->priv->tooltip_primary),
                                    TRAY_ICON_DEFAULT_TOOLTIP);
                break;
        }
}
