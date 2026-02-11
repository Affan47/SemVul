wnck_window_opened_cb (WnckScreen *screen,
                       WnckWindow *window,
                       GvaProcess *process)
{
        GPid pid;


        pid = (GPid) wnck_window_get_pid (window);


        if (pid != gva_process_get_pid (process) && pid != 0)
                return;


        g_object_weak_unref (
                g_object_ref (process), (GWeakNotify)
                wnck_weak_notify_cb, screen);


        g_object_set_data_full (
                G_OBJECT (window), "process", process,
                (GDestroyNotify) g_object_unref);


        g_signal_handler_disconnect (screen, window_opened_handler_id);
        window_opened_handler_id = 0;

        wnck_window_initialize (window);

        g_signal_connect (
                window, "geometry-changed",
                G_CALLBACK (wnck_window_timeout_reset), NULL);

        g_signal_connect (
                window, "state-changed",
                G_CALLBACK (wnck_window_timeout_reset), NULL);

        g_signal_connect (
                screen, "window-closed",
                G_CALLBACK (wnck_window_closed_cb), NULL);

        gva_main_cursor_normal ();
}
