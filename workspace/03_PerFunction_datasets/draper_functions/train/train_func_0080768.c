gGraphDrawRectangle (const void *context, double x, double y, double width,
		     double height)
{

    gGraphContextPtr ctx = (gGraphContextPtr) context;
    if (!ctx)
	return GGRAPH_INVALID_PAINT_CONTEXT;
    if (ctx->signature == GG_GRAPHICS_CONTEXT_MAGIC_SIGNATURE ||
	ctx->signature == GG_GRAPHICS_SVG_CONTEXT_MAGIC_SIGNATURE ||
	ctx->signature == GG_GRAPHICS_PDF_CONTEXT_MAGIC_SIGNATURE)
	;
    else
	return GGRAPH_INVALID_PAINT_CONTEXT;
    cairo_rectangle (ctx->cairo, x, y, width, height);
    set_current_brush (ctx);
    cairo_fill_preserve (ctx->cairo);
    set_current_pen (ctx);
    cairo_stroke (ctx->cairo);
    return GGRAPH_OK;
}
