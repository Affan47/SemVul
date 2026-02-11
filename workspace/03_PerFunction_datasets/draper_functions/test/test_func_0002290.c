xqueue_add_callback(ObtXQueueFunc f, gpointer data)
{
    guint i;

    g_return_if_fail(f != NULL);

    for (i = 0; i < n_callbacks; ++i)
        if (callbacks[i].func == f && callbacks[i].data == data)
            return;

    callbacks = g_renew(ObtXQueueCB, callbacks, n_callbacks + 1);
    callbacks[n_callbacks].func = f;
    callbacks[n_callbacks].data = data;
    ++n_callbacks;
}
