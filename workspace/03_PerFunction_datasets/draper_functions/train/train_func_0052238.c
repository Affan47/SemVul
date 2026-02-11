pan_layout_update_idle_cb(gpointer data)
{
	PanWindow *pw = data;
	gint width;
	gint height;
	gint scroll_x;
	gint scroll_y;

	if (pw->size > PAN_IMAGE_SIZE_THUMB_LARGE ||
	    (pw->exif_date_enable && (pw->layout == PAN_LAYOUT_TIMELINE || pw->layout == PAN_LAYOUT_CALENDAR)))
		{
		if (!pw->cache_list && !pw->cache_todo)
			{
			pan_cache_fill(pw, pw->dir_fd);
			if (pw->cache_todo)
				{
				pan_window_message(pw, _("Reading image data..."));
				return TRUE;
				}
			}
		if (pw->cache_todo)
			{
			pw->cache_count++;
			pw->cache_tick++;
			if (pw->cache_count == pw->cache_total)
				{
				pan_window_message(pw, _("Sorting..."));
				}
			else if (pw->cache_tick > 9)
				{
				gchar *buf;

				buf = g_strdup_printf("%s %d / %d", _("Reading image data..."),
						      pw->cache_count, pw->cache_total);
				pan_window_message(pw, buf);
				g_free(buf);

				pw->cache_tick = 0;
				}

			if (pan_cache_step(pw)) return TRUE;

			pw->idle_id = 0;
			return FALSE;
			}
		}

	pan_layout_compute(pw, pw->dir_fd, &width, &height, &scroll_x, &scroll_y);

	pan_window_zoom_limit(pw);

	if (width > 0 && height > 0)
		{
		gdouble align;

		DEBUG_1("Canvas size is %d x %d", width, height);

		pan_grid_build(pw, width, height, 1000);

		pixbuf_renderer_set_tiles(PIXBUF_RENDERER(pw->imd->pr), width, height,
					  PAN_TILE_SIZE, PAN_TILE_SIZE, 10,
					  pan_window_request_tile_cb,
					  pan_window_dispose_tile_cb, pw, 1.0);

		if (scroll_x == 0 && scroll_y == 0)
			{
			align = 0.0;
			}
		else
			{
			align = 0.5;
			}
		pixbuf_renderer_scroll_to_point(PIXBUF_RENDERER(pw->imd->pr), scroll_x, scroll_y, align, align);
		}

	pan_window_message(pw, NULL);

	pw->idle_id = 0;
	return FALSE;
}
