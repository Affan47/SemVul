entangle_overlay_box_set_child(EntangleOverlayBox *box,
                               GtkWidget **child,
                               GdkWindow *childWin,
                               GtkWidget *widget)
{
    GtkWidget *oldChild = *child;

    if (oldChild) {
        g_object_ref(oldChild);
        gtk_container_remove(GTK_CONTAINER(box), oldChild);
    }

    *child = widget;
    if (*child) {
        gtk_widget_set_parent_window(widget, childWin);
        gtk_container_add(GTK_CONTAINER(box), *child);
    }

    if (oldChild) {
        g_object_unref(oldChild);
    }
}
