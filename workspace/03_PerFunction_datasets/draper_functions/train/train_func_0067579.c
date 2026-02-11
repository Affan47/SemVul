show_opaque(WINDOW *stswin, WINDOW *txtwin, bool before, int active)
{
    int n;
    int top, bottom;

    if (before) {
	werase(stswin);
    }
    for (n = 0; n < (int) SIZEOF(bool_funcs); ++n) {
	show_keyword(stswin, n, active, bool_funcs[n].name);

	to_result(stswin, n, before);
	wprintw(stswin, "%c", bool_funcs[n].func(txtwin, -1) ? 'T' : 'F');
    }

    show_keyword(stswin, n, active, "wgetparent");
    to_result(stswin, n, TRUE);
    wprintw(stswin, "%p", wgetparent(txtwin));

    ++n;
    show_keyword(stswin, n, active, "wgetscrreg");
    to_result(stswin, n, TRUE);
    if (wgetscrreg(txtwin, &top, &bottom) == OK)
	wprintw(stswin, "%d,%d", top, bottom);

    wnoutrefresh(stswin);
    return active;
}
