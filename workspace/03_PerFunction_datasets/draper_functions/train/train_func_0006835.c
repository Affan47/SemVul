strng1(void)
{
    wattrset(treescrn2, A_BOLD | A_BLINK);
    set_color(treescrn2, COLOR_WHITE);

    mvwaddch(treescrn2, 3, 13, (chtype) '\'');
    mvwaddch(treescrn2, 3, 12, (chtype) ':');
    mvwaddch(treescrn2, 3, 11, (chtype) '.');

    wattroff(treescrn2, A_BOLD | A_BLINK);
    unset_color(treescrn2);

    wrefresh(treescrn2);
    wrefresh(w_del_msg);
    return (0);
}
