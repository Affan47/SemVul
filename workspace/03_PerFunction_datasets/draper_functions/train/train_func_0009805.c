GdipFlush (GpGraphics *graphics, GpFlushIntention intention)
{
	cairo_surface_t* surface;

	if (!graphics)
		return InvalidParameter;

	surface = cairo_get_target (graphics->ct);
	cairo_surface_flush (surface);

#ifdef CAIRO_HAS_QUARTZ_SURFACE
	if (graphics->type == gtOSXDrawable) {
		CGRect rect;

		rect.origin.x = 0;
		rect.origin.y = 0;
		rect.size.width = graphics->bounds.Width;
		rect.size.height = graphics->bounds.Height;
		void *image = CGBitmapContextCreateImage (cairo_quartz_surface_get_cg_context (surface));
		CGContextDrawImage (graphics->cg_context, rect, image);
		CGImageRelease (image);
	}
#endif
	return Ok;
}
