bus_panel_proxy_set_cursor_location (BusPanelProxy *panel,
                                     gint           x,
                                     gint           y,
                                     gint           w,
                                     gint           h)
{
    g_assert (BUS_IS_PANEL_PROXY (panel));
    g_dbus_proxy_call ((GDBusProxy *)panel,
                       "SetCursorLocation",
                       g_variant_new ("(iiii)", x, y, w, h),
                       G_DBUS_CALL_FLAGS_NONE,
                       -1, NULL, NULL, NULL);
}
