win_textbuffer_clear(window_t *win)
{
    window_textbuffer_t *dwin = win->data;
    int i;

    win->attr.fgset = gli_override_fg_set;
    win->attr.bgset = gli_override_bg_set;
    win->attr.fgcolor = gli_override_fg_set ? gli_override_fg_val : 0;
    win->attr.bgcolor = gli_override_bg_set ? gli_override_bg_val : 0;
    win->attr.reverse = FALSE;

    dwin->ladjw = dwin->radjw = 0;
    dwin->ladjn = dwin->radjn = 0;

    dwin->spaced = 0;
    dwin->dashed = 0;

    dwin->numchars = 0;

    for (i = 0; i < dwin->scrollback; i++)
    {
        dwin->lines[i].len = 0;
        dwin->lines[i].lpic = 0;
        dwin->lines[i].rpic = 0;
        dwin->lines[i].lhyper = 0;
        dwin->lines[i].rhyper = 0;
        dwin->lines[i].lm = 0;
        dwin->lines[i].rm = 0;
        dwin->lines[i].newline = 0;
        dwin->lines[i].dirty = 1;
        dwin->lines[i].repaint = 0;
    }

    dwin->lastseen = 0;
    dwin->scrollpos = 0;
    dwin->scrollmax = 0;

    for (i = 0; i < dwin->height; i++)
        touch(dwin, i);


}
