ario_cover_handler_get_covers (ArioCoverHandler *cover_handler)
{
        ARIO_LOG_FUNCTION_START;
        GArray *size;
        GSList *covers;
        gboolean ret;
        ArioCoverHandlerData *data;

        while ((data = (ArioCoverHandlerData *) g_async_queue_try_pop (cover_handler->priv->queue))) {
                if (ario_cover_cover_exists (data->artist, data->album)) {
                        ario_cover_handler_free_data (data);
                        continue;
                }

                covers = NULL;
                size = g_array_new (TRUE, TRUE, sizeof (int));


                ret = ario_cover_manager_get_covers (ario_cover_manager_get_instance (),
                                                     data->artist,
                                                     data->album,
                                                     data->path,
                                                     &size,
                                                     &covers,
                                                     GET_FIRST_COVER);


                if (ret && ario_cover_size_is_valid (g_array_index (size, int, 0))) {
                        ret = ario_cover_save_cover (data->artist,
                                                     data->album,
                                                     g_slist_nth_data (covers, 0),
                                                     g_array_index (size, int, 0),
                                                     OVERWRITE_MODE_SKIP);

                        if (ret) {
                                ario_cover_handler_load_pixbuf (cover_handler, FALSE);
                                g_idle_add ((GSourceFunc) ario_cover_handler_cover_changed, cover_handler);
                        }
                }
                ario_cover_handler_free_data (data);

                g_array_free (size, TRUE);
                g_slist_foreach (covers, (GFunc) g_free, NULL);
                g_slist_free (covers);
        }
        cover_handler->priv->thread = NULL;

        return NULL;
}
