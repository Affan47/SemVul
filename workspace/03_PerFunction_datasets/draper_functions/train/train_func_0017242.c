SetValues(Widget gcurrent,
			 Widget grequest,
			 Widget gnew,
			 ArgList args,
			 Cardinal *num_args)
{
    ArtTreeWidget	current = (ArtTreeWidget)gcurrent;
    ArtTreeWidget	new     = (ArtTreeWidget)gnew;
    Boolean		redisplay = False;
    Boolean		do_layout = False;

    if (new->arttree.vertical != current->arttree.vertical)
	do_layout = True;

    if (new->arttree.rubber_pixel     != current->arttree.rubber_pixel     ||
	new->arttree.foreground_pixel != current->arttree.foreground_pixel ||
	new->arttree.font             != current->arttree.font             ||
	new->arttree.inner_pixel      != current->arttree.inner_pixel      ||
	new->arttree.outer_pixel      != current->arttree.outer_pixel      ||
	new->arttree.inner_dashed     != current->arttree.inner_dashed     ||
	new->arttree.outer_dashed     != current->arttree.outer_dashed) {
	free_gcs(new);
	init_gcs(new);
	redisplay = True;
    }

    if (new->arttree.font != current->arttree.font) {
	init_node_sizes(new);
	do_layout = True;
    }

    if (new->arttree.internal_node_width !=
	current->arttree.internal_node_width ||
	new->arttree.internal_node_height !=
	current->arttree.internal_node_height ||
	new->arttree.pixmap_spacing != current->arttree.pixmap_spacing ||
	new->arttree.node_columns != current->arttree.node_columns ||
	new->arttree.node_rows != current->arttree.node_rows) {
	init_node_sizes(new);
	if (new->arttree.root)
	    update_private_data(new, new->arttree.root);
	do_layout = True;

    }

    if (new->arttree.row_spacing != current->arttree.row_spacing ||
	new->arttree.internal_width != current->arttree.internal_width ||
	new->arttree.internal_height != current->arttree.internal_height ||
	new->shadow.shadow_width != current->shadow.shadow_width) {
	do_layout = True;
	redisplay = True;
    }

    if (new->arttree.root != current->arttree.root) {
	if (current->arttree.root)
	    free_private_data(current->arttree.root);
	if (new->arttree.root)
	    init_private_data(new, new->arttree.root);
	do_layout = True;
	if (!new->scrollable.suspended)
	    redisplay = True;
    }

    if (do_layout) {
	layout(new);
	redisplay = True;
    }

    return redisplay;
}
