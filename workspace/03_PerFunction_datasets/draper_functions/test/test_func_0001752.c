bs_window_get_wm_icon_name(BSWindow *bswin, GError **error)
{
    gchar *data = NULL, *name;
    gulong nitems;
    if (bs_xutil_get_window_property(bswin->window,
                                     WM_ICON_NAME, AnyPropertyType, 8, &nitems,
                                     (guchar **)&data, error) != 0)
        return NULL;

    name = g_strdup(data);
    XFree(data);
    return name;
}
