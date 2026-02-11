paint_pois()
{


	int pixel_x, pixel_y, x, y;
	float lat, lon;
	GSList *list;
	GdkColor color;
	static GdkGC *gc;


	if (!gc)
		gc = gdk_gc_new(pixmap);
	color.green = 0;
	color.blue = 60000;
	color.red = 0;
	gdk_gc_set_rgb_fg_color(gc, &color);


	if(global_show_pois)
	{
		get_pois();

		for(list = poi_list; list != NULL; list = list->next)
		{
			poi_t *p = list->data;

			GdkPixbuf *photo_icon = get_poi_icon (p);
			int icon_width = gdk_pixbuf_get_width (photo_icon);
			int icon_height = gdk_pixbuf_get_width (photo_icon);

			lat = deg2rad(p->lat_deg);
			lon = deg2rad(p->lon_deg);


			pixel_x = lon2pixel(global_zoom, lon);
			pixel_y = lat2pixel(global_zoom, lat);

			x = pixel_x - global_x;
			y = pixel_y - global_y;

			p->screen_x = x;
			p->screen_y = y;


			if(!photo_icon)
			{
				gdk_draw_arc (
					pixmap,

					gc,
					TRUE,
					x-4, y-4,
					8,8,
					0,23040);
			}
			else
			{
				gdk_draw_pixbuf (
					pixmap,
					NULL,
					photo_icon,
					0,0,
					x - icon_width/2, y - icon_height/2,
					-1, -1,
					GDK_RGB_DITHER_NONE, 0, 0);

			}

			gtk_widget_queue_draw_area (
					map_drawable,
					x - icon_width/2, y - icon_height/2,
					icon_width, icon_height);

			printf("POI: %s lat %f - lon %f\n",p->keywords,p->lat_deg, p->lon_deg);
		}
	}
}
