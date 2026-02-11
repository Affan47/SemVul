scrolloneline(window_textbuffer_t *dwin, int forced)
{
    int i;

    dwin->lastseen ++;
    dwin->scrollmax ++;

    if (dwin->scrollmax > dwin->scrollback - 1
            || dwin->lastseen > dwin->scrollback - 1)
        scrollresize(dwin);

    if (dwin->lastseen >= dwin->height)
        dwin->scrollpos ++;

    if (dwin->scrollpos > dwin->scrollmax - dwin->height + 1)
        dwin->scrollpos = dwin->scrollmax - dwin->height + 1;
    if (dwin->scrollpos < 0)
        dwin->scrollpos = 0;

    if (forced)
        dwin->dashed = 0;
    dwin->spaced = 0;

    dwin->lines[0].len = dwin->numchars;
    dwin->lines[0].newline = forced;

    for (i = dwin->scrollback - 1; i > 0; i--)
    {
        memcpy(dwin->lines+i, dwin->lines+i-1, sizeof(tbline_t));
        if (i < dwin->height)
            touch(dwin, i);
    }

    if (dwin->radjn)
        dwin->radjn--;
    if (dwin->radjn == 0)
        dwin->radjw = 0;
    if (dwin->ladjn)
        dwin->ladjn--;
    if (dwin->ladjn == 0)
        dwin->ladjw = 0;

    touch(dwin, 0);
    dwin->lines[0].len = 0;
    dwin->lines[0].newline = 0;
    dwin->lines[0].lm = dwin->ladjw;
    dwin->lines[0].rm = dwin->radjw;
    dwin->lines[0].lpic = NULL;
    dwin->lines[0].rpic = NULL;
    dwin->lines[0].lhyper = 0;
    dwin->lines[0].rhyper = 0;
    memset(dwin->chars, ' ', TBLINELEN * 4);
    memset(dwin->attrs, 0, TBLINELEN * sizeof(attr_t));

    dwin->numchars = 0;

    touchscroll(dwin);
}
