paste_create(const char *name)
{
    gpaint_paste *paste = g_new0(gpaint_paste, 1);
    gpaint_tool *tool = GPAINT_TOOL(paste);

    debug_fn();
    tool->name = name;
    tool->cursor = gdk_cursor_new(GDK_X_CURSOR);
    tool->destroy        = paste_destroy;
    tool->select         = paste_select;
    tool->deselect       = paste_deselect;
    tool->button_press   = paste_button_press;
    tool->button_release = paste_button_release;
    tool->motion         = paste_motion;
    tool->key_release    = paste_key_release;
    return tool;
}
