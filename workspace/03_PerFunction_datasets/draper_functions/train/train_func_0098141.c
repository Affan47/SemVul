event_seat_active_session_changed_copy (CkLogSeatActiveSessionChangedEvent *event,
                                        CkLogSeatActiveSessionChangedEvent *event_copy)
{
        g_assert (event != NULL);
        g_assert (event_copy != NULL);

        event_copy->seat_id = g_strdup (event->seat_id);
        event_copy->session_id = g_strdup (event->session_id);
}
