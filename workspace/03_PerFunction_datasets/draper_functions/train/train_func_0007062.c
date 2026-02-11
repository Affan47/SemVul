window_dialog_up_changed_cb (GSWindow   *window,
                             GParamSpec *pspec,
                             GSManager  *manager)
{
        gboolean up;

        up = gs_window_is_dialog_up (window);
        gs_debug ("Handling window dialog up changed: %s", up ? "up" : "down");
        if (up) {
                handle_window_dialog_up (manager, window);
        } else {
                handle_window_dialog_down (manager, window);
        }
}
