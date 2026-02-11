on_session_save(AnjutaShell *shell, AnjutaSessionPhase phase, AnjutaSession *session, AnjutaWindow *win) {
    gchar *geometry, *layout_file;
    GdkWindowState state;

    if (phase != ANJUTA_SESSION_PHASE_NORMAL)
        return;


    state = gdk_window_get_state(gtk_widget_get_window(GTK_WIDGET(win)));
    if (state & GDK_WINDOW_STATE_MAXIMIZED) {
        anjuta_session_set_int(session, "Anjuta", "Maximized", 1);
    }
    if (state & GDK_WINDOW_STATE_FULLSCREEN) {
        anjuta_session_set_int(session, "Anjuta", "Fullscreen", 1);
    }


    if (!(state & GDK_WINDOW_STATE_MAXIMIZED) || !(state & GDK_WINDOW_STATE_FULLSCREEN)) {
        geometry = anjuta_window_get_geometry(win);
        if (geometry)
            anjuta_session_set_string(session, "Anjuta", "Geometry", geometry);
        g_free(geometry);
    }


    layout_file = g_build_filename(anjuta_session_get_session_directory(session), "dock-layout.xml", NULL);
    anjuta_window_layout_save(win, layout_file, NULL);
    g_free(layout_file);
}
