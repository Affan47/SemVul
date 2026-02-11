win_textgrid_move_cursor(window_t *win, int xpos, int ypos)
{
    window_textgrid_t *dwin = win->data;


    if (xpos < 0)
        xpos = 32767;
    if (ypos < 0)
        ypos = 32767;

    dwin->curx = xpos;
    dwin->cury = ypos;
}
