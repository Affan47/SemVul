gtk_hex_size_allocate(GtkWidget *w, GtkAllocation *alloc) {
	GtkHex *gh;
	GtkAllocation my_alloc;
	GtkBorder padding;
	GtkRequisition sb_req;
	GtkStateFlags state;
	GtkStyleContext *context;
	gint border_width;

	gh = GTK_HEX(w);
	hide_cursor(gh);

	recalc_displays(gh, alloc->width, alloc->height);

	gtk_widget_set_allocation(w, alloc);
	if(gtk_widget_get_realized(w))
		gdk_window_move_resize (gtk_widget_get_window(w),
								alloc->x,
								alloc->y,
								alloc->width,
								alloc->height);

	border_width = gtk_container_get_border_width(GTK_CONTAINER(w));

	context = gtk_widget_get_style_context (w);
	state = gtk_widget_get_state_flags (w);
	gtk_style_context_get_padding (context, state, &padding);

	my_alloc.x = border_width + padding.left;
	my_alloc.y = border_width + padding.top;
	my_alloc.height = MAX (alloc->height - 2 * border_width - padding.top - padding.bottom, 1);
	if(gh->show_offsets) {
		my_alloc.width = 8*gh->char_width;
		gtk_widget_size_allocate(gh->offsets, &my_alloc);
		gtk_widget_queue_draw(gh->offsets);
		my_alloc.x += padding.left + padding.right + my_alloc.width;
	}

	gtk_widget_get_requisition(gh->scrollbar, &sb_req);

	my_alloc.width = gh->xdisp_width;
	gtk_widget_size_allocate(gh->xdisp, &my_alloc);
	my_alloc.x = alloc->width - border_width - sb_req.width;
	my_alloc.y = border_width;
	my_alloc.width = sb_req.width;
	my_alloc.height = MAX(alloc->height - 2*border_width, 1);
	gtk_widget_size_allocate(gh->scrollbar, &my_alloc);
	my_alloc.x -= gh->adisp_width + padding.left;
	my_alloc.y = border_width + padding.top;
	my_alloc.width = gh->adisp_width;
	my_alloc.height = MAX (alloc->height - 2 * border_width - padding.top - padding.bottom, 1);
	gtk_widget_size_allocate(gh->adisp, &my_alloc);

	show_cursor(gh);
}
