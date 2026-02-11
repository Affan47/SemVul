test_chgat(void)
{
    STATUS st;

    init_status(stdscr, &st);

    do {
	switch (st.ch) {
	case '.':
	    chgat(st.count, st.attr, st.pair, (void *) 0);
	    touch_if_needed(stdscr, st.y_val);
	    break;
	case ',':
	    mvchgat(0, 0, st.count, st.attr, st.pair, (void *) 0);
	    touch_if_needed(stdscr, 0);
	    move(st.y_val, st.x_val);
	    break;
	case 'w':
	    do_subwindow(stdscr, &st, test_wchgat);
	    break;
	case 'q':
	    return;
	default:
	    update_status(stdscr, &st);
	    break;
	}
    } while ((st.ch = getch()) != ERR);
}
