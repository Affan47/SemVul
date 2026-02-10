GdipGetImageGraphicsContext (GpImage *image, GpGraphics **graphics)
{
	GpGraphics	*gfx;
	cairo_surface_t	*surface;
	cairo_pattern_t	*filter;

	if (!image || !graphics)
		return InvalidParameter;


	if (image->type == ImageTypeMetafile) {
		GpMetafile *mf = (GpMetafile*)image;
		if (!mf->recording)
			return OutOfMemory;
		*graphics = gdip_metafile_graphics_new (mf);
		return *graphics ? Ok : OutOfMemory;
	}

	if (!image->active_bitmap)
		return InvalidParameter;


	switch (image->active_bitmap->pixel_format) {
	case PixelFormat24bppRGB:
	case PixelFormat32bppARGB:
	case PixelFormat32bppPARGB:
	case PixelFormat32bppRGB:
		break;
	default:
		return OutOfMemory;
	}

	surface = cairo_image_surface_create_for_data ((BYTE*) image->active_bitmap->scan0, image->cairo_format,
				image->active_bitmap->width, image->active_bitmap->height, image->active_bitmap->stride);

	gfx = gdip_graphics_new (surface);
	gfx->dpi_x = image->active_bitmap->dpi_horz <= 0 ? gdip_get_display_dpi () : image->active_bitmap->dpi_horz;
	gfx->dpi_y = image->active_bitmap->dpi_vert <= 0 ? gdip_get_display_dpi () : image->active_bitmap->dpi_vert;
	cairo_surface_destroy (surface);

	gfx->image = image;
	gfx->type = gtMemoryBitmap;
	filter = cairo_pattern_create_for_surface (image->surface);
	cairo_pattern_set_filter (filter, gdip_get_cairo_filter (gfx->interpolation));
	cairo_pattern_destroy (filter);
	*graphics = gfx;
	return Ok;
}
