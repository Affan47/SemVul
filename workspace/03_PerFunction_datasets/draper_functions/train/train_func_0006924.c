_nc_freewin(WINDOW *win)
{
    WINDOWLIST *p, *q;
    int i;
    int result = ERR;

    T((T_CALLED("_nc_freewin(%p)"), win));

    if (win != 0) {
	if (_nc_try_global(curses) == 0) {
	    q = 0;
	    for (each_window(p)) {
		if (&(p->win) == win) {
		    remove_window_from_screen(win);
		    if (q == 0)
			_nc_windows = p->next;
		    else
			q->next = p->next;

		    if (!(win->_flags & _SUBWIN)) {
			for (i = 0; i <= win->_maxy; i++)
			    FreeIfNeeded(win->_line[i].text);
		    }
		    free(win->_line);
		    free(p);

		    result = OK;
		    T(("...deleted win=%p", win));
		    break;
		}
		q = p;
	    }
	    _nc_unlock_global(curses);
	}
    }
    returnCode(result);
}
