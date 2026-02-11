draw_node(ArtTreeWidget w, ART_TREE_NODE *node)
{
    Display	*disp = XtDisplay(w);
    Window	win   = XtWindow(w);
    int		x, y;

    if (node->hook->selected && w->shadow.arm_gc != 0)
	XFillRectangle(disp, win, w->shadow.arm_gc,
		       node->hook->x, node->hook->y,
		       w->arttree.node_width, w->arttree.node_height);
    ShadowDrawShadows((ShadowWidget)w,
		      node->hook->x, node->hook->y,
		      w->arttree.node_width, w->arttree.node_height,
		      node->hook->selected);

    if (node->hook->inner)
	draw_inner_border(w, node);

    if (node->hook->outer)
	draw_outer_border(w, node);

    x = node->hook->x + w->arttree.internal_node_width +
	w->shadow.shadow_width;
    y = node->hook->y;
    if (node->hook->pixmap != None) {
	if (w->arttree.depth_one)
	    XCopyPlane(disp, node->hook->pixmap, win,
		       w->arttree.default_gc, 0, 0,
		       w->arttree.pixmap_width, w->arttree.pixmap_height,
		       x, y + (int)(w->arttree.node_height -
				    w->arttree.pixmap_height) / 2 +
		       (node->hook->selected ? 1 : 0), 1);
	else
	    XCopyArea(disp, node->hook->pixmap, win,
		      w->arttree.default_gc, 0, 0,
		      w->arttree.pixmap_width, w->arttree.pixmap_height,
		      x, y + (int)(w->arttree.node_height -
				   w->arttree.pixmap_height) / 2 +
		      (node->hook->selected ? 1 : 0));
	x += w->arttree.pixmap_width + w->arttree.pixmap_spacing;
    }
    y += w->arttree.font->ascent + w->arttree.internal_node_height +
	w->shadow.shadow_width;
    if (node->hook->selected)
	y++;
    if (node->label)
	XDrawString(disp, win, w->arttree.default_gc, x, y,
		    node->label, node->hook->label_len);
}
