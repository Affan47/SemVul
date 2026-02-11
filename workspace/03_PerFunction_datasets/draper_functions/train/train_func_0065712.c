set_correct_cursor(void)
{
    GdkModifierType state;
    cursor_type new_cursor;

    if (cursors == NULL)
        init_cursors();

    gdk_display_get_pointer(gdk_display_get_default(), NULL, NULL, NULL,
                            &state);

    if (state & GDK_BUTTON3_MASK && (state & GDK_BUTTON1_MASK) == 0)
        new_cursor = CURSOR_RECT_ZOOM;

    else if (state & GDK_SHIFT_MASK) {
        if (state & GDK_CONTROL_MASK)
            new_cursor = CURSOR_ZOOM_ROTATE;
        else
            new_cursor = CURSOR_ZOOM;

    } else if (state & GDK_CONTROL_MASK)
        new_cursor = CURSOR_ROTATE;

    else if (state & GDK_BUTTON1_MASK)
        new_cursor = CURSOR_MOVE;

    else
        new_cursor = CURSOR_DEFAULT;

    if (new_cursor != current_type) {
        current_type = new_cursor;
        show_cursor();
    }

    return FALSE;
}
