write_to_log (CkEventLogger    *logger)
{
        CkLogEvent event;
        GError    *error;
        gboolean   res;

        memset (&event, 0, sizeof (CkLogEvent));

        event.type = CK_LOG_EVENT_SEAT_SESSION_ADDED;
        g_get_current_time (&event.timestamp);

        event.event.seat_session_added.session_id = "Session1";

        error = NULL;
        res = ck_event_logger_queue_event (logger, &event, &error);
        if (! res) {
                g_warning ("Unable to queue event: %s", error->message);
                g_error_free (error);
        }

        return TRUE;
}
