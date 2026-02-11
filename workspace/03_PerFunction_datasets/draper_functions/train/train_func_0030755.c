test_wchgat(WINDOW *win)
{
    STATUS st;

    init_status(win, &st);

    do {
	switch (st.ch) {
	case '.':
	    wchgat(win, st.count, st.attr, st.pair, (void *) 0);
	    touch_if_needed(win, st.y_val);
	    break;
	case ',':
	    mvwchgat(win, 0, 0, st.count, st.attr, st.pair, (void *) 0);
	    touch_if_needed(win, 0);
	    wmove(win, st.y_val, st.x_val);
	    break;
	case 'w':
	    do_subwindow(win, &st, test_wchgat);
	    break;
	case 'q':
	    return;
	default:
	    update_status(win, &st);
	    break;
	}
    } while ((st.ch = wgetch(win)) != ERR);
}
