book_monitor_event_timeout_cb  (gpointer data)
{
        DhBook     *book = data;
        DhBookPriv *priv = GET_PRIVATE (book);


        switch (priv->monitor_event)
        {
        case BOOK_MONITOR_EVENT_DELETED:


                g_object_ref (book);
		g_signal_emit (book, signals[BOOK_DELETED], 0);
                g_object_unref (book);
                break;
        case BOOK_MONITOR_EVENT_UPDATED:


                g_object_ref (book);
		g_signal_emit (book, signals[BOOK_UPDATED], 0);
                g_object_unref (book);
                break;
        default:
                break;
        }


        priv->monitor_event = BOOK_MONITOR_EVENT_NONE;


        g_object_unref (book);
        return FALSE;
}
