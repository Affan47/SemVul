_set_cursor_location_internal (IBusIMContext *ibusimcontext)
{
    GdkRectangle area;

    if(ibusimcontext->client_window == NULL ||
       ibusimcontext->ibuscontext == NULL) {
        return FALSE;
    }

    area = ibusimcontext->cursor_area;
    if (area.x == -1 && area.y == -1 && area.width == 0 && area.height == 0) {
#if GTK_CHECK_VERSION (2, 91, 0)
        area.x = 0;
        area.y += gdk_window_get_height (ibusimcontext->client_window);
#else
        gint w, h;
        gdk_drawable_get_size (ibusimcontext->client_window, &w, &h);
        area.y += h;
        area.x = 0;
#endif
    }

    gdk_window_get_root_coords (ibusimcontext->client_window,
                                area.x, area.y,
                                &area.x, &area.y);
    ibus_input_context_set_cursor_location (ibusimcontext->ibuscontext,
                                            area.x,
                                            area.y,
                                            area.width,
                                            area.height);
    return FALSE;
}
