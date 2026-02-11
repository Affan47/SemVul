music_button_handle_state_changed (GvaMusicButton *music_button,
                                   GstMessage *message)
{
        GtkWidget *image;
        GtkIconSize icon_size;
        GstState old_state;
        GstState new_state;
        GstState pending;
        gchar *stock_id;

        image = gtk_button_get_image (GTK_BUTTON (music_button));
        gtk_image_get_stock (GTK_IMAGE (image), &stock_id, &icon_size);

        gst_message_parse_state_changed (
                message, &old_state, &new_state, &pending);

        switch (new_state)
        {
                case GST_STATE_NULL:
                        stock_id = GTK_STOCK_MEDIA_PLAY;
                        break;

                case GST_STATE_READY:
                        stock_id = GTK_STOCK_MEDIA_PLAY;
                        break;

                case GST_STATE_PAUSED:
                        if (music_button->priv->seeking)
                                stock_id = GTK_STOCK_MEDIA_PAUSE;
                        else
                                stock_id = GTK_STOCK_MEDIA_PLAY;
                        break;

                case GST_STATE_PLAYING:
                        stock_id = GTK_STOCK_MEDIA_PAUSE;
                        music_button->priv->seeking = FALSE;
                        break;

                default:
                        break;
        }

        music_button_set_status (music_button, NULL);
        gtk_image_set_from_stock (GTK_IMAGE (image), stock_id, icon_size);

        g_log (
                G_LOG_DOMAIN, GVA_DEBUG_GST,
                "%s -> %s -> %s",
                gst_element_state_get_name (old_state),
                gst_element_state_get_name (new_state),
                gst_element_state_get_name (pending));
}
