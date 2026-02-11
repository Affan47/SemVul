signal_occurred(GSource *source, GSourceFunc callback,
                                gpointer data)
{
    guint i;
    sigset_t oldset;
    guint fired[NUM_SIGNALS];


    sigprocmask(SIG_SETMASK, &all_signals_set, &oldset);


    for (i = 0; i < NUM_SIGNALS; ++i) {
        fired[i] = signals_fired[i];
        signals_fired[i] = 0;
    }
    signal_fired = FALSE;

    sigprocmask(SIG_SETMASK, &oldset, NULL);


    for (i = 0; i < NUM_SIGNALS; ++i) {
        while (fired[i]) {
            GSList *it;
            for (it = callbacks[i]; it; it = g_slist_next(it)) {
                const ObtSignalCallback *cb = it->data;
                cb->func(i, cb->data);
            }
            --fired[i];
        }
    }

    return TRUE;
}
