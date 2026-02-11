ario_shell_sync_window_state (ArioShell *shell)
{
        ARIO_LOG_FUNCTION_START;
        int width = ario_conf_get_integer (PREF_WINDOW_WIDTH, PREF_WINDOW_WIDTH_DEFAULT);
        int height = ario_conf_get_integer (PREF_WINDOW_HEIGHT, PREF_WINDOW_HEIGHT_DEFAULT);
        gboolean maximized = ario_conf_get_boolean (PREF_WINDOW_MAXIMIZED, PREF_WINDOW_MAXIMIZED_DEFAULT);


        gtk_window_set_default_size (GTK_WINDOW (shell),
                                     width, height);
        gtk_window_resize (GTK_WINDOW (shell),
                           width, height);


        if (maximized)
                gtk_window_maximize (GTK_WINDOW (shell));
        else
                gtk_window_unmaximize (GTK_WINDOW (shell));
}
