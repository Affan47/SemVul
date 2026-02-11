gdl_dock_item_grip_show_handle (GdlDockItemGrip *grip)
{
    g_return_if_fail (grip != NULL);
    if (!grip->priv->handle_shown) {
        grip->priv->handle_shown = TRUE;
        gdl_dock_item_grip_showhide_handle (grip);
        if (grip->priv->title_window != NULL) {
            GdkCursor *cursor = gdk_cursor_new_for_display (gtk_widget_get_display (GTK_WIDGET (grip)), GDK_HAND2);
            gdk_window_set_cursor (grip->priv->title_window, cursor);
            g_object_unref (cursor);
        }
    };
}
