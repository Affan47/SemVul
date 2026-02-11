ArtTreeNodeNotifyLabel(Widget gw, ART_TREE_NODE *node)
{
    ArtTreeWidget	w = (ArtTreeWidget)gw;
    int			width;

    if (!node->hook)
	return;

    width = w->arttree.node_width -
	2 * (w->arttree.internal_node_width + w->shadow.shadow_width);
    if (node->hook->pixmap != None)
	width -= w->arttree.pixmap_width + w->arttree.pixmap_spacing;
    if (node->label)
	node->hook->label_len =
	    MyXWidthToChars(w->arttree.font, node->label,
			    strlen(node->label), width);
    else
	node->hook->label_len = 0;

    if (w->scrollable.suspended || !XtIsRealized((Widget)w))
	return;

    if (w->arttree.rubberbanding)
	draw_rubberband(w);
    XClearArea(XtDisplay(w), XtWindow(w), node->hook->x, node->hook->y,
	       w->arttree.node_width, w->arttree.node_height, False);
    draw_node(w, node);
    if (w->arttree.rubberbanding)
	draw_rubberband(w);
    XFlush(XtDisplay(w));
}
