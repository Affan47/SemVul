gg_convert_image_to_grid_int16 (const gGraphImagePtr img)
{

    int x;
    int y;
    void *pixels;
    short value;
    unsigned char *p_in;
    short *p_out;

    if (img->pixel_format != GG_PIXEL_GRID)
	return GGRAPH_INVALID_IMAGE;

    if (img->sample_format == GGRAPH_SAMPLE_INT && img->bits_per_sample == 16)
	return GGRAPH_OK;

    pixels = malloc (img->width * img->height * sizeof (short));
    if (!pixels)
	return GGRAPH_INSUFFICIENT_MEMORY;
    for (y = 0; y < img->height; y++)
      {

	  p_in = img->pixels + (y * img->scanline_width);
	  p_out = pixels;
	  p_out += (y * img->width);
	  for (x = 0; x < img->width; x++)
	    {

		if (img->sample_format == GGRAPH_SAMPLE_UINT
		    && img->bits_per_sample == 16)
		  {
		      value = (short) *((unsigned short *) p_in);
		      p_in += sizeof (unsigned short);
		  }
		if (img->sample_format == GGRAPH_SAMPLE_INT
		    && img->bits_per_sample == 32)
		  {
		      value = (short) *((int *) p_in);
		      p_in += sizeof (int);
		  }
		if (img->sample_format == GGRAPH_SAMPLE_UINT
		    && img->bits_per_sample == 32)
		  {
		      value = (short) *((unsigned int *) p_in);
		      p_in += sizeof (unsigned int);
		  }
		if (img->sample_format == GGRAPH_SAMPLE_FLOAT
		    && img->bits_per_sample == 32)
		  {
		      value = (short) *((float *) p_in);
		      p_in += sizeof (float);
		  }
		if (img->sample_format == GGRAPH_SAMPLE_FLOAT
		    && img->bits_per_sample == 64)
		  {
		      value = (short) *((double *) p_in);
		      p_in += sizeof (double);
		  }

		*p_out++ = value;
	    }
      }

    free (img->pixels);
    img->pixels = pixels;
    img->pixel_format = GG_PIXEL_GRID;
    img->scanline_width = img->width * sizeof (short);
    img->pixel_size = sizeof (short);
    img->sample_format = GGRAPH_SAMPLE_INT;
    img->bits_per_sample = 16;
    return GGRAPH_OK;
}
