gGraphGetContextRgbArray (const void *context, unsigned char **rgbArray)
{

    int width;
    int height;
    int x;
    int y;
    unsigned char *p_in;
    unsigned char *p_out;
    unsigned char *rgb;
    int little_endian = gg_endian_arch ();
    gGraphContextPtr ctx = (gGraphContextPtr) context;

    *rgbArray = NULL;
    if (!ctx)
	return GGRAPH_INVALID_PAINT_CONTEXT;
    if (ctx->signature != GG_GRAPHICS_CONTEXT_MAGIC_SIGNATURE)
	return GGRAPH_INVALID_PAINT_CONTEXT;

    width = cairo_image_surface_get_width (ctx->surface);
    height = cairo_image_surface_get_height (ctx->surface);
    rgb = malloc (width * height * 3);
    if (!rgb)
	return GGRAPH_INSUFFICIENT_MEMORY;

    p_in = cairo_image_surface_get_data (ctx->surface);
    p_out = rgb;
    for (y = 0; y < height; y++)
      {
	  for (x = 0; x < width; x++)
	    {
		unsigned char r;
		unsigned char g;
		unsigned char b;
		if (little_endian)
		  {
		      b = *p_in++;
		      g = *p_in++;
		      r = *p_in++;
		      p_in++;
		  }
		else
		  {
		      p_in++;
		      r = *p_in++;
		      g = *p_in++;
		      b = *p_in++;
		  }
		*p_out++ = r;
		*p_out++ = g;
		*p_out++ = b;
	    }
      }
    *rgbArray = rgb;
    return GGRAPH_OK;
}
