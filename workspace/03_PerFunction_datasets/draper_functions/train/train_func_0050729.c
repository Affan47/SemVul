closed_freehand_create(const char *name)
{
    gpaint_closed_freehand *cfh = g_new0(gpaint_closed_freehand, 1);
    g_assert(cfh);

    GPAINT_TOOL(cfh)->name = name;
    GPAINT_TOOL(cfh)->cursor = gdk_cursor_new(GDK_PENCIL);
    GPAINT_TOOL(cfh)->destroy        = freehand_destroy;
    GPAINT_TOOL(cfh)->select         = freehand_select;
    GPAINT_TOOL(cfh)->deselect       = freehand_deselect;
    GPAINT_TOOL(cfh)->attribute      = freehand_attribute;
    GPAINT_TOOL(cfh)->button_press   = freehand_button_press;
    GPAINT_TOOL(cfh)->motion         = freehand_draw_line;
    GPAINT_TOOL(cfh)->button_release = freehand_button_release;

    cfh->points = point_array_new();
    return GPAINT_TOOL(cfh);
}
