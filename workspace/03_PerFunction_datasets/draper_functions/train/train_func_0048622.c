win_textgrid_putchar_uni(window_t *win, glui32 ch)
{
    window_textgrid_t *dwin = win->data;
    tgline_t *ln;


    if (dwin->curx < 0)
    {
        dwin->curx = 0;
    }
    else if (dwin->curx >= dwin->width)
    {
        dwin->curx = 0;
        dwin->cury++;
    }
    if (dwin->cury < 0)
        dwin->cury = 0;
    else if (dwin->cury >= dwin->height)
        return;

    if (ch == '\n')
    {

        dwin->cury++;
        dwin->curx = 0;
        return;
    }

    touch(dwin, dwin->cury);

    ln = &(dwin->lines[dwin->cury]);
    ln->chars[dwin->curx] = ch;
    ln->attrs[dwin->curx] = win->attr;

    dwin->curx++;


}
