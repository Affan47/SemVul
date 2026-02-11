ario_audioscrobbler_print_queue (ArioAudioscrobbler *audioscrobbler, gboolean submission)
{
        ARIO_LOG_FUNCTION_START
        GList *l;
        AudioscrobblerEntry *entry;

        if (submission) {
                l = audioscrobbler->priv->submission->head;
                ARIO_LOG_DBG ("Audioscrobbler submission (%d entries): ",
                              g_queue_get_length (audioscrobbler->priv->submission));

        } else {
                l = audioscrobbler->priv->queue->head;
                ARIO_LOG_DBG ("Audioscrobbler queue (%d entries): ",
                              g_queue_get_length (audioscrobbler->priv->queue));
        }

        for (; l != NULL; l = g_list_next (l)) {
                char timestamp[30];
                entry = (AudioscrobblerEntry *) l->data;

                ARIO_LOG_DBG ("      artist: %s", entry->artist);
                ARIO_LOG_DBG ("      album: %s", entry->album);
                ARIO_LOG_DBG ("      title: %s", entry->title);
                ARIO_LOG_DBG ("     length: %d", entry->length);
                if (entry->encoded_play_time) {
                        ARIO_LOG_DBG ("  timestamp: %s", entry->encoded_play_time);
                } else {
                        strftime (timestamp, 30, SCROBBLER_DATE_FORMAT,
                                        gmtime (&entry->play_time));
                        ARIO_LOG_DBG ("  timestamp: %s", timestamp);
                }
        }
}
