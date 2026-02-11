gGraphDrawBitmap (const void *context, const void *bitmap, int x, int y)
{

    gGraphBitmapPtr bmp = (gGraphBitmapPtr) bitmap;
    gGraphContextPtr ctx = (gGraphContextPtr) context;

    if (!ctx)
	return GGRAPH_INVALID_PAINT_CONTEXT;
    if (ctx->signature == GG_GRAPHICS_CONTEXT_MAGIC_SIGNATURE ||
	ctx->signature == GG_GRAPHICS_SVG_CONTEXT_MAGIC_SIGNATURE ||
	ctx->signature == GG_GRAPHICS_PDF_CONTEXT_MAGIC_SIGNATURE)
	;
    else
	return GGRAPH_INVALID_PAINT_CONTEXT;

    if (!bmp)
	return GGRAPH_INVALID_PAINT_BITMAP;
    if (bmp->signature != GG_GRAPHICS_BITMAP_MAGIC_SIGNATURE)
	return GGRAPH_INVALID_PAINT_BITMAP;

    cairo_save (ctx->cairo);
    cairo_scale (ctx->cairo, 1, 1);
    cairo_translate (ctx->cairo, x, y);
    cairo_set_source (ctx->cairo, bmp->pattern);
    cairo_rectangle (ctx->cairo, 0, 0, bmp->width, bmp->height);
    cairo_fill (ctx->cairo);
    cairo_restore (ctx->cairo);
    return GGRAPH_OK;
}
