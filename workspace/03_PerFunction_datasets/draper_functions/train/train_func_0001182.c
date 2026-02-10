set_inner(Widget gw, XEvent *event,
		      String *params, Cardinal *no_params)
{
    ArtTreeWidget	w = (ArtTreeWidget)gw;
    int			x, y;
    ART_TREE_NODE	*node;

    if (!w->arttree.active || !get_event_xy(event, &x, &y))
	return;

    node = find_node_by_coordinates(w, w->arttree.root, x, y);
    if (node) {
	XtCallbackList	c_list = w->arttree.inner_callback;

	ArtTreeNodeSetInner((Widget)w, node, True);

	if (c_list)
	    XtCallCallbackList((Widget)w, c_list, (XtPointer)node);
    }
}
