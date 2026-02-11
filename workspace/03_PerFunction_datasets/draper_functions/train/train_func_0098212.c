draw_score_pegs (int line, int b, int c, GtkWidget *widget) {
	int i;
	int x, y;
	int offset;

	GdkPixbuf *tmp;

	for (i = 0; i< b+c; i++) {
		if (pixbuf)
			g_object_unref (pixbuf);
		if (i<b){
			offset = 0;
		}
		else {
			offset = 1;
		}
		pixbuf = gdk_pixbuf_new_subpixbuf (tileset_bg,
						   ballmed*8,
						   ballmed/2*offset,
						   ballmed/2, ballmed/2);
		tmp = pixbuf;

		pixbuf = gdk_pixbuf_scale_simple (pixbuf,
						  ballmed/2-1,
						  ballmed/2-1,
						  GDK_INTERP_BILINEAR);

		g_object_unref (tmp);


		x = grid_xpad + grid_sz * (GRID_COLS+1) + (grid_sz/2 * (i%2));

		y = grid_ypad + grid_sz * line + ((int)i/2)*grid_sz/2;

		if (i>1) y-=0.5;

		gm_debug ("line: %d, i:%d\n",line,i);

		gdk_draw_pixbuf (pixmap,
				 NULL,
				 pixbuf,
				 0, 0,
				 x+1,
				 y+1,
				 -1, -1, GDK_RGB_DITHER_MAX, 0, 0);
		gtk_widget_queue_draw_area (widget, x, y, grid_sz/2, grid_sz/2);
	}
}
