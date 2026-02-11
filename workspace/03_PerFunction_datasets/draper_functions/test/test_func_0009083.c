paint_from_rgb_cache(GtkWidget *widget, struct map_cache *cache, GdkRectangle *area)
{
	unsigned char *dat;
	if (!area_in_cache(area, cache)) {
		err_printf("paint_from_cache: oops - area not in cache\n");
		d3_printf("area is %d by %d starting at %d,%d\n",
			  area->width, area->height, area->x, area->y);
		d3_printf("cache is %d by %d starting at %d,%d\n",
			  cache->w, cache->h, cache->x, cache->y);

	}
	dat = cache->dat + (area->x - cache->x
		+ (area->y - cache->y) * cache->w) * 3;
	gdk_draw_rgb_image (widget->window, widget->style->fg_gc[GTK_STATE_NORMAL],
			     area->x, area->y, area->width, area->height,
			     GDK_RGB_DITHER_MAX, dat, cache->w*3);
}
