draw_branches(ArtTreeWidget w, ART_TREE_NODE *node)
{
    Display		*disp = XtDisplay(w);
    Window		win = XtWindow(w);
    ART_TREE_NODE	*child = node->child1;
    GC			gc1, gc2;
    int			x, y, y0;

    if (!child)
	return;

    if (w->arttree.vertical) {
	x = node->hook->x + w->arttree.column_spacing;
	y0 = node->hook->y + w->arttree.node_height - 1;
	y = child->hook->y + w->arttree.node_height / 2;
    } else {
	x = (node->hook->x + w->arttree.node_width + child->hook->x)/2;
	y = y0 = node->hook->y + w->arttree.node_height/2;
	XDrawLine(disp, win,
		  w->shadow.line_mode ? w->shadow.light_gc : w->shadow.dark_gc,
		  node->hook->x + w->arttree.node_width, y - 1, x + 1, y - 1);
	XDrawLine(disp, win, w->shadow.light_gc,
		  node->hook->x + w->arttree.node_width, y, x + 1, y);
    }

    for (;;) {
	if (child->hook->dashed) {
	    if (w->shadow.line_mode)
		gc1 = w->arttree.light_dashed_gc;
	    else
		gc1 = w->arttree.dark_dashed_gc;
	    gc2 = w->arttree.light_dashed_gc;
	} else {
	    if (w->shadow.line_mode)
		gc1 = w->shadow.light_gc;
	    else
		gc1 = w->shadow.dark_gc;
	    gc2 = w->shadow.light_gc;
	}
	XDrawLine(disp, win, gc1, x + 1, y - 1, child->hook->x, y - 1);
	XDrawLine(disp, win, gc2, x + 1, y, child->hook->x, y);

	child = child->sibling;
	if (!child)
	    break;
	y = child->hook->y + w->arttree.node_height/2;
    }

    XDrawLine(disp, win,
	      w->shadow.line_mode ? w->shadow.light_gc : w->shadow.dark_gc,
	      x - 1, y0 + 1, x - 1, y + 1);
    XDrawLine(disp, win, w->shadow.light_gc, x, y0 + 1, x, y + 1);

}
