hitori_button_release_cb (GtkWidget *drawing_area, GdkEventButton *event, Hitori *hitori)
{
	gint width, height;
	gfloat cell_size;
	HitoriVector pos;
	HitoriUndo *undo;
	gboolean recheck = FALSE;

	if (hitori->processing_events == FALSE)
		return FALSE;

	width = gdk_window_get_width (gtk_widget_get_window (hitori->drawing_area));
	height = gdk_window_get_height (gtk_widget_get_window (hitori->drawing_area));


	if (height < width)
		width = height;
	else if (width < height)
		height = width;

	cell_size = width / hitori->board_size;


	pos.x = (guchar) ((event->x - hitori->drawing_area_x_offset) / cell_size);
	pos.y = (guchar) ((event->y - hitori->drawing_area_y_offset) / cell_size);

	if (pos.x >= hitori->board_size || pos.y >= hitori->board_size)
		return FALSE;


	undo = g_new (HitoriUndo, 1);
	undo->cell = pos;
	undo->undo = hitori->undo_stack;
	undo->redo = NULL;

	if (event->state & GDK_SHIFT_MASK && event->state & GDK_CONTROL_MASK) {

		hitori->board[pos.x][pos.y].status ^= CELL_TAG1;
		hitori->board[pos.x][pos.y].status ^= CELL_TAG2;
		undo->type = UNDO_TAGS;
	} else if (event->state & GDK_SHIFT_MASK) {

		hitori->board[pos.x][pos.y].status ^= CELL_TAG1;
		undo->type = UNDO_TAG1;
	} else if (event->state & GDK_CONTROL_MASK) {

		hitori->board[pos.x][pos.y].status ^= CELL_TAG2;
		undo->type = UNDO_TAG2;
	} else {

		hitori->board[pos.x][pos.y].status ^= CELL_PAINTED;
		undo->type = UNDO_PAINT;
		recheck = TRUE;
	}

	hitori->made_a_move = TRUE;

	if (hitori->undo_stack != NULL)
		hitori->undo_stack->redo = undo;
	hitori->undo_stack = undo;
	g_simple_action_set_enabled (hitori->undo_action, TRUE);


	hitori_cancel_hinting (hitori);


	gtk_widget_queue_draw (hitori->drawing_area);


	if (recheck == TRUE)
		hitori_check_win (hitori);

	return FALSE;
}
