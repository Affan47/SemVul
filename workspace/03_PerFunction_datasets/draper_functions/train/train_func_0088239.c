anjuta_window_layout_load(AnjutaWindow *win, const gchar *layout_filename, const gchar *name) {
    g_return_if_fail (ANJUTA_IS_WINDOW (win));

    if (!layout_filename || !gdl_dock_layout_load_from_file(win->layout_manager, layout_filename)) {
        gchar *filename;

        filename = g_build_filename(get_data_dir(), "dock-layout.xml", NULL);
        DEBUG_PRINT("Layout = %s", filename);
        if (!gdl_dock_layout_load_from_file(win->layout_manager, filename))
            g_warning ("Loading layout from '%s' failed!!", filename);
        g_free(filename);
    }

    if (!gdl_dock_layout_load_layout(win->layout_manager, name))
        g_warning ("Loading layout failed!!");
}
