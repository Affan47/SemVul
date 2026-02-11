show_help(bool * keyhelp)
{
    werase(helpwin);
    if (*keyhelp) {
	help1();
	*keyhelp = FALSE;
    } else {
	help2();
	*keyhelp = TRUE;
    }
    wrefresh(helpwin);
}
