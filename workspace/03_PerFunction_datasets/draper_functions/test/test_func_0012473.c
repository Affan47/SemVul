w_active_win(w_data *d, w_winspec *rwin)
{
    geo_t *geo = &(rwin->geo);
    geo_t scr;
    long (*frm)[] = &(rwin->_frame.s);
    if (get_active_window(d->_dpy, &(rwin->_w)) != 0)
	return -1;
    if (get_window_geometry(d->_dpy, rwin->_w, &(rwin->geo), &(rwin->_frame.s))
	    != 0)
	return -1;
    if (get_root_geometry(d->_dpy, &(rwin->rootgeo)) != 0)
	return -1;
    if (find_window_screen(d, rwin, &scr) != 0) {


	intersect_geo(&(rwin->rootgeo), &scr, &(rwin->rootgeo));
    } else {
	if (d->_scrgeo != NULL) {
	    intersect_geo(&(rwin->rootgeo), &(d->_scrgeo[0]), &(rwin->rootgeo));
	}
    }
    debugln("current desktop's workarea at %d,%d %ux%u\n", rwin->rootgeo.x,
	    rwin->rootgeo.y, rwin->rootgeo.w, rwin->rootgeo.h);
    return 0;
}
