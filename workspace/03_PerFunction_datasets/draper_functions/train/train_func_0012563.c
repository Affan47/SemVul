pr_source_tile_new(PixbufRenderer *pr, gint x, gint y)
{
	SourceTile *st = NULL;
	gint count;

	g_return_val_if_fail(pr->source_tile_width >= 1 && pr->source_tile_height >= 1, NULL);

	if (pr->source_tiles_cache_size < 4) pr->source_tiles_cache_size = 4;

	count = g_list_length(pr->source_tiles);
	if (count >= pr->source_tiles_cache_size)
		{
		GList *work;

		work = g_list_last(pr->source_tiles);
		while (work && count >= pr->source_tiles_cache_size)
			{
			SourceTile *needle;

			needle = work->data;
			work = work->prev;

			if (!pr_source_tile_visible(pr, needle))
				{
				pr->source_tiles = g_list_remove(pr->source_tiles, needle);

				if (pr->func_tile_dispose)
					{
					pr->func_tile_dispose(pr, needle->x, needle->y,
							      pr->source_tile_width, pr->source_tile_height,
							      needle->pixbuf, pr->func_tile_data);
					}

				if (!st)
					{
					st = needle;
					}
				else
					{
					pr_source_tile_free(needle);
					}

				count--;
				}
			}
		}

	if (!st)
		{
		st = g_new0(SourceTile, 1);
		st->pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8,
					    pr->source_tile_width, pr->source_tile_height);
		}

	st->x = ROUND_DOWN(x, pr->source_tile_width);
	st->y = ROUND_DOWN(y, pr->source_tile_height);
	st->blank = TRUE;

	pr->source_tiles = g_list_prepend(pr->source_tiles, st);

	return st;
}
