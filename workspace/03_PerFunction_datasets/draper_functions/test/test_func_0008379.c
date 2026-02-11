ArtTreeNodeSetDashed(Widget gw, ART_TREE_NODE *node, int dashed)
{
    ART_TREE_NODE	*parent = node->parent;
    ArtTreeWidget	w = (ArtTreeWidget)gw;

    if (!parent || !node->hook)
	return;

    node->hook->dashed = dashed;
    if (w->scrollable.suspended || !XtIsRealized((Widget)w))
	return;

    if (w->arttree.rubberbanding)
	draw_rubberband(w);
    if (dashed)
	if (w->arttree.vertical)
	    ;
	else
	    XClearArea(XtDisplay(w), XtWindow(w),
		       parent->hook->x + w->arttree.node_width,
		       parent->hook->y, w->arttree.column_spacing,
		       parent->hook->bb_height, False);
    draw_branches(w, parent);
    if (w->arttree.rubberbanding)
	draw_rubberband(w);
    XFlush(XtDisplay(w));
}
