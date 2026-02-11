xqueue_next_local(XEvent *event_return)
{
    g_return_val_if_fail(q != NULL, FALSE);
    g_return_val_if_fail(event_return != NULL, FALSE);

    if (!qnum) read_events(FALSE);
    if (qnum) {
        *event_return = q[qstart];
        pop(qstart);
        return TRUE;
    }

    return FALSE;
}
