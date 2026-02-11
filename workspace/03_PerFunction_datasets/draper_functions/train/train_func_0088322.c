fill_create(const char *name)
{
    gpaint_fill *fill = g_new0(gpaint_fill, 1);
    g_assert(fill);

    GPAINT_TOOL(fill)->name = name;
    GPAINT_TOOL(fill)->cursor = gdk_cursor_new(GDK_CROSSHAIR);
    GPAINT_TOOL(fill)->destroy = fill_destroy;
    GPAINT_TOOL(fill)->button_press = fill_bounded_area;
    return GPAINT_TOOL(fill);
}
