glk_window_move_cursor(window_t *win, glui32 xpos, glui32 ypos)
{
    if (!win)
    {
        gli_strict_warning("window_move_cursor: invalid ref");
        return;
    }

    switch (win->type)
    {
        case wintype_TextGrid:
            win_textgrid_move_cursor(win, xpos, ypos);
            break;
        default:
            gli_strict_warning("window_move_cursor: not a TextGrid window");
            break;
    }
}
