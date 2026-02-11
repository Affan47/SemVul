dock_move_start (GtkWidget * window, gint x, gint y)
{
    DockWindow * dw = find_window (windows, window);
    g_return_if_fail (dw);

    dock_sync ();

    last_x = x;
    last_y = y;


    clear_docked ();
    dw->docked = TRUE;
    if (dw->main)
        find_docked (dw, DOCK_TYPE_ANY);
}
