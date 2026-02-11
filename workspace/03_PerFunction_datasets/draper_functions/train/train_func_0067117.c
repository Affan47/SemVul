raw_monochrome (unsigned char *p, int width, int height)
{

    int x;
    int y;
    int line_width;
    gGraphImagePtr img = gg_image_create (GG_PIXEL_PALETTE, width, height, 8, 1,
					  GGRAPH_SAMPLE_UINT, NULL, NULL);

    if (!img)
	return NULL;

    img->max_palette = 2;
    img->palette_red[0] = 255;
    img->palette_green[0] = 255;
    img->palette_blue[0] = 255;
    img->palette_red[1] = 0;
    img->palette_green[1] = 0;
    img->palette_blue[1] = 0;

    line_width = width / 8;
    if ((line_width * 8) < width)
	line_width++;

    for (y = 0; y < height; y++)
      {
	  unsigned char *p_in = p + (y * line_width);
	  unsigned char *p_out = img->pixels + (y * img->scanline_width);
	  unsigned char byte = 0x00;
	  unsigned char px;
	  int pixel;
	  int pos = 0;
	  for (x = 0; x < width; x++)
	    {
		if (pos == 0)
		    byte = *p_in++;
		pixel = 0;
		switch (pos)
		  {
		  case 0:
		      px = byte & 0x80;
		      if (px == 0x80)
			  pixel = 1;
		      break;
		  case 1:
		      px = byte & 0x40;
		      if (px == 0x40)
			  pixel = 1;
		      break;
		  case 2:
		      px = byte & 0x20;
		      if (px == 0x20)
			  pixel = 1;
		      break;
		  case 3:
		      px = byte & 0x10;
		      if (px == 0x10)
			  pixel = 1;
		      break;
		  case 4:
		      px = byte & 0x08;
		      if (px == 0x08)
			  pixel = 1;
		      break;
		  case 5:
		      px = byte & 0x04;
		      if (px == 0x04)
			  pixel = 1;
		      break;
		  case 6:
		      px = byte & 0x02;
		      if (px == 0x02)
			  pixel = 1;
		      break;
		  case 7:
		      px = byte & 0x01;
		      if (px == 0x01)
			  pixel = 1;
		      break;
		  };
		*p_out++ = pixel;
		pos++;
		if (pos > 7)
		  {
		      byte = 0x00;
		      pos = 0;
		  }
	    }
      }
    return img;
}
