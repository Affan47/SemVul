pan_item_image_draw(PanWindow *pw, PanItem *pi, GdkPixbuf *pixbuf, PixbufRenderer *pr,
			 gint x, gint y, gint width, gint height)
{
	gint rx, ry, rw, rh;

	if (util_clip_region(x, y, width, height,
			     pi->x, pi->y, pi->width, pi->height,
			     &rx, &ry, &rw, &rh))
		{
		if (pi->pixbuf)
			{
			gdk_pixbuf_composite(pi->pixbuf, pixbuf, rx - x, ry - y, rw, rh,
					     (gdouble) pi->x - x,
					     (gdouble) pi->y - y,
					     1.0, 1.0, GDK_INTERP_NEAREST,
					     pi->color_a);
			}
		else
			{
			pixbuf_draw_rect_fill(pixbuf,
					      rx - x, ry - y, rw, rh,
					      pi->color2_r, pi->color2_g, pi->color2_b, pi->color2_a);
			}
		}

	return (pi->pixbuf == NULL);
}
