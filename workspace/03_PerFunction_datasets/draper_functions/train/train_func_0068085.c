histogram_imager_make_thumbnail (HistogramImager *self, guint max_width, guint max_height)
{
    float aspect = ((float)self->width) / ((float)self->height);
    guint width, height;
    GdkPixbuf *thumb;


    histogram_imager_update_image (self);


    if (aspect > 1) {
	width = max_width;
	height = width / aspect;
    }
    else {
	height = max_height;
	width = height * aspect;
    }
    width = MAX(width, 5);
    height = MAX(height, 5);
    thumb = gdk_pixbuf_scale_simple (self->image, width, height, GDK_INTERP_BILINEAR);


    image_add_checkerboard(thumb);


    if (width < 128 || height < 128)
	image_adjust_levels(thumb);


    image_add_thumbnail_frame(thumb);

    return thumb;
}
