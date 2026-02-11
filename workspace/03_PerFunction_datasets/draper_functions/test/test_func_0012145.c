ario_audioscrobbler_add_to_queue (ArioAudioscrobbler *audioscrobbler,
                                  AudioscrobblerEntry *entry)
{
        ARIO_LOG_FUNCTION_START
        if (g_queue_get_length (audioscrobbler->priv->queue) < MAX_QUEUE_SIZE){
                g_queue_push_tail (audioscrobbler->priv->queue, entry);
                audioscrobbler->priv->queue_changed = TRUE;
                audioscrobbler->priv->queue_count++;
                return TRUE;
        } else {
                ARIO_LOG_INFO ("Queue is too long.  Not adding song to queue");
                g_free (audioscrobbler->priv->status_msg);
                audioscrobbler->priv->status = QUEUE_TOO_LONG;
                audioscrobbler->priv->status_msg = NULL;
                return FALSE;
        }
}
