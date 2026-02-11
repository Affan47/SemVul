GDrawDrawRect(GWindow w, GRect *rect, Color col) {
    if ( col!=COLOR_UNKNOWN )
	(w->display->funcs->drawRect)(w,rect,col);
}
