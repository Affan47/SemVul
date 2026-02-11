canvas_setcursor(t_canvas *x, unsigned int cursornum)
{
    static t_canvas *xwas;
    static unsigned int cursorwas;
    if (cursornum >= sizeof(cursorlist)/sizeof *cursorlist)
    {
        bug("canvas_setcursor");
        return;
    }
    if (xwas != x || cursorwas != cursornum)
    {
        sys_vgui(".x%lx configure -cursor %s\n", x, cursorlist[cursornum]);
        xwas = x;
        cursorwas = cursornum;
    }
}
