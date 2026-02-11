anjuta_window_unmaximize(AnjutaShell *shell, GError **error) {
    AnjutaWindow *win = NULL;


    g_return_if_fail(ANJUTA_IS_WINDOW (shell));
    win = ANJUTA_WINDOW (shell);


    g_return_if_fail(win->maximized);


    gdl_dock_layout_load_layout(win->layout_manager, "back-up");
    gdl_dock_layout_delete_layout(win->layout_manager, "back-up");


    win->maximized = FALSE;
}
