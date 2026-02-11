gGraphDrawRoundedRectangle (const void *context, double x, double y,
			    double width, double height, double radius)
{

    double degrees = M_PI / 180.0;
    gGraphContextPtr ctx = (gGraphContextPtr) context;
    if (!ctx)
	return GGRAPH_INVALID_PAINT_CONTEXT;
    if (ctx->signature == GG_GRAPHICS_CONTEXT_MAGIC_SIGNATURE ||
	ctx->signature == GG_GRAPHICS_SVG_CONTEXT_MAGIC_SIGNATURE ||
	ctx->signature == GG_GRAPHICS_PDF_CONTEXT_MAGIC_SIGNATURE)
	;
    else
	return GGRAPH_INVALID_PAINT_CONTEXT;
    cairo_new_sub_path (ctx->cairo);
    cairo_arc (ctx->cairo, x + width - radius, y + radius, radius,
	       -90 * degrees, 0 * degrees);
    cairo_arc (ctx->cairo, x + width - radius, y + height - radius, radius,
	       0 * degrees, 90 * degrees);
    cairo_arc (ctx->cairo, x + radius, y + height - radius, radius,
	       90 * degrees, 180 * degrees);
    cairo_arc (ctx->cairo, x + radius, y + radius, radius, 180 * degrees,
	       270 * degrees);
    cairo_close_path (ctx->cairo);
    set_current_brush (ctx);
    cairo_fill_preserve (ctx->cairo);
    set_current_pen (ctx);
    cairo_stroke (ctx->cairo);
    return GGRAPH_OK;
}
