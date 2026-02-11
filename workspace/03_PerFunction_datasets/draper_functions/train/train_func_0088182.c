gg_convert_image_to_palette (const gGraphImagePtr img)
{

    int x;
    int y;
    void *pixels;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char index;
    unsigned char *p_in;
    unsigned char *p_out;

    if (img->pixel_format == GG_PIXEL_RGB || img->pixel_format == GG_PIXEL_RGBA
	|| img->pixel_format == GG_PIXEL_ARGB
	|| img->pixel_format == GG_PIXEL_BGR
	|| img->pixel_format == GG_PIXEL_BGRA
	|| img->pixel_format == GG_PIXEL_GRAYSCALE
	|| img->pixel_format == GG_PIXEL_PALETTE)
	;
    else
	return GGRAPH_INVALID_IMAGE;

    if (img->pixel_format == GG_PIXEL_PALETTE)
	return GGRAPH_OK;

    pixels = malloc (img->width * img->height);
    if (!pixels)
	return GGRAPH_INSUFFICIENT_MEMORY;
    img->max_palette = 0;
    for (y = 0; y < img->height; y++)
      {

	  p_in = img->pixels + (y * img->scanline_width);
	  p_out = pixels;
	  p_out += (y * img->width);
	  for (x = 0; x < img->width; x++)
	    {

		if (img->pixel_format == GG_PIXEL_RGB)
		  {
		      red = *p_in++;
		      green = *p_in++;
		      blue = *p_in++;
		  }
		else if (img->pixel_format == GG_PIXEL_RGBA)
		  {
		      red = *p_in++;
		      green = *p_in++;
		      blue = *p_in++;
		      p_in++;
		  }
		else if (img->pixel_format == GG_PIXEL_ARGB)
		  {
		      p_in++;
		      blue = *p_in++;
		      green = *p_in++;
		      red = *p_in++;
		  }
		else if (img->pixel_format == GG_PIXEL_BGR)
		  {
		      blue = *p_in++;
		      green = *p_in++;
		      red = *p_in++;
		      p_in++;
		  }
		else if (img->pixel_format == GG_PIXEL_BGRA)
		  {
		      blue = *p_in++;
		      green = *p_in++;
		      red = *p_in++;
		      p_in++;
		  }
		else if (img->pixel_format == GG_PIXEL_GRAYSCALE)
		  {
		      red = *p_in++;
		      green = red;
		      blue = red;
		  }

		index = gg_match_palette (img, red, green, blue);
		*p_out++ = index;
	    }
      }

    free (img->pixels);
    img->pixels = pixels;
    img->pixel_format = GG_PIXEL_PALETTE;
    img->scanline_width = img->width;
    img->pixel_size = 1;
    return GGRAPH_OK;
}
