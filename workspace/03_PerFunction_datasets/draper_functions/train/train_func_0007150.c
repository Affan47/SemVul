pm_drag_drop(GtkWidget *widget, GdkDragContext *drag_context, gint x, gint y, guint time, gpointer user_data) {
    GdkAtom target;

    gp_remove_autoscroll_row_timeout(widget);

    target = gtk_drag_dest_find_target(widget, drag_context, NULL);

    if (target != GDK_NONE) {
        gtk_drag_get_data(widget, drag_context, target, time);
        return TRUE;
    }
    return FALSE;
}
