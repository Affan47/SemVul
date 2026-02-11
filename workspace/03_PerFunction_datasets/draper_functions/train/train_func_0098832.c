goto_mouse
	(
	int mx, int my,
	bool delay_send
	)
	{
	GdkRectangle oldbox = viewbox;
	int oldtx = tx, oldty = ty;


	tx = (mx*c_num_tiles)/draw->allocation.width;
	ty = (my*c_num_tiles)/draw->allocation.height;
	int cx = tx/c_tiles_per_chunk, cy = ty/c_tiles_per_chunk;
	if (cx > c_num_chunks - 2)
		cx = c_num_chunks - 2;
	if (cy > c_num_chunks - 2)
		cy = c_num_chunks - 2;
	tx = cx*c_tiles_per_chunk;
	ty = cy*c_tiles_per_chunk;

	gtk_adjustment_set_value(hadj, cx);
	gtk_adjustment_set_value(vadj, cy);

	if (tx != oldtx || ty != oldty)
		{
		if (send_location_timer != -1)
			gtk_timeout_remove(send_location_timer);
		if (delay_send)
			send_location_timer = gtk_timeout_add(333,
					delayed_send_location, this);
		else
			{
			send_location();
			send_location_timer = -1;
			}
		GdkRectangle newbox;
		GdkRectangle dirty;
		newbox.x = (cx*draw->allocation.width)/c_num_chunks,
	    	newbox.y = (cy*draw->allocation.height)/c_num_chunks;
		newbox.width = oldbox.width;
		newbox.height = oldbox.height;
		gdk_rectangle_union(&oldbox, &newbox, &dirty);

		dirty.x -= 4; dirty.y -= 4;
		dirty.width += 8; dirty.height += 8;
		render(&dirty);
		}
	}
