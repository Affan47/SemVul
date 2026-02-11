glist_scroll_selbymouse(GList *gl, GEvent *event) {
    int loff=0, xoff=0, pos;

    if ( event->u.mouse.y<gl->g.inner.y ) {
	if ( gl->loff>0 ) loff = -1;
    } else if ( event->u.mouse.y >= gl->g.inner.y+gl->g.inner.height ) {
	int top = GListTopInWindow(gl,gl->ltot-1);
	if ( gl->loff<top ) loff = 1;
    }
    if ( event->u.mouse.x<gl->g.inner.x ) {
	xoff = -GDrawPointsToPixels(gl->g.base,6);
    } else if ( event->u.mouse.x >= gl->g.inner.x+gl->g.inner.width ) {
	xoff = GDrawPointsToPixels(gl->g.base,6);
    }
    GListScrollBy(gl,loff,xoff);
    pos = GListIndexFromPos(gl,event->u.mouse.y);
    if ( pos==-1 || pos == gl->end )
	;
    else if ( !gl->multiple_sel ) {
	GListClearSel(gl);
	gl->ti[pos]->selected = true;
	gl->start = gl->end = pos;
	_ggadget_redraw(&gl->g);
    } else {
	GListExpandSelection(gl,pos);
	gl->end = pos;
	_ggadget_redraw(&gl->g);
    }
}
