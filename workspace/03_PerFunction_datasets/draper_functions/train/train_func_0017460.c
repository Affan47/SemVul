gp_image_draw ( GpImage *image,
                GdkDrawable *drawable,
                GdkGC *gc,
				gint x, gint y,
                gint width, gint height )
{
	gboolean	resized;
	GdkPixbuf   *pixbuf;
	gint		wo,ho,w,h;

	g_return_if_fail ( GP_IS_IMAGE (image) );

	wo = gp_image_get_width  (image);
	ho = gp_image_get_height (image);
	w = (width  == -1)?wo:width;
	h = (height == -1)?ho:height;

	if ( w == wo && h == ho )
	{
		pixbuf  = image->priv->pixbuf;
		resized = FALSE;
	}
	else
	{
		pixbuf = gdk_pixbuf_scale_simple ( image->priv->pixbuf, w, h, GDK_INTERP_HYPER );
		resized = TRUE;
	}

	gdk_draw_pixbuf	( drawable,
			          gc,
			     	  pixbuf,
			          0, 0,
			          x, y,
			          -1, -1,
			          GDK_RGB_DITHER_NORMAL,
		              0, 0);
	if ( resized )
	{
		g_object_unref ( pixbuf );
	}
}
