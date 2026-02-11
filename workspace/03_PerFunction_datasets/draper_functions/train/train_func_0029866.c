move_menus(MENU * current, int by_y, int by_x)
{
    if (move_menu(mpBanner, current, by_y, by_x) != ERR) {
	erase();
	wnoutrefresh(stdscr);
	move_menu(mpFile, current, by_y, by_x);
	move_menu(mpSelect, current, by_y, by_x);
#ifdef TRACE
	move_menu(mpTrace, current, by_y, by_x);
#endif
	doupdate();
    }
}
