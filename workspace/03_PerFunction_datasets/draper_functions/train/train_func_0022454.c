event_read(GSource *source, GSourceFunc callback,
                           gpointer data)
{
    XEvent ev;

    while (xqueue_next_local(&ev)) {
        guint i;
        for (i = 0; i < n_callbacks; ++i)
            callbacks[i].func(&ev, callbacks[i].data);
    }

    return TRUE;
}
