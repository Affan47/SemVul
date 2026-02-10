generate_histogram_rgb (Histogram histogram, gGraphImagePtr img)
{
    int x;
    int y;
    int red;
    int green;
    int blue;
    unsigned char *p_in;
    ColorFreq *col;

    zero_histogram_rgb (histogram);

    for (y = 0; y < img->height; y++)
      {
	  p_in = img->pixels + (y * img->scanline_width);
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
		else if (img->pixel_format == GG_PIXEL_PALETTE)
		  {
		      int index = *p_in++;
		      red = img->palette_red[index];
		      green = img->palette_green[index];
		      blue = img->palette_blue[index];
		  }
		col = &histogram[(red >> R_SHIFT) * MR
				 + (green >> G_SHIFT) * MG + (blue >> B_SHIFT)];
		(*col)++;
	    }
      }
}
