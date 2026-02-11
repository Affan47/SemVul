convert_pic (char *base_name, int format)
{
  FILE *ifp;
  unsigned char pic[MAX_IMAGE_SIZE];
  int res, image_size, image_width, net_width, camera_header, components;
  struct pixmap *pp2;

  DBG (127, "convert_pic() called\n");


  if ((ifp = fopen (base_name, "rb")) == NULL)
    {
      DBG (10, "convert_pic: error: cannot open %s for reading\n", base_name);
      return -1;
    }

  if (fread (pic, COMET_HEADER_SIZE, 1, ifp) != 1)
    {
      DBG (10, "convert_pic: error: cannot read COMET header\n");
      fclose (ifp);
      return -1;
    }

  if (strncmp ((char *) pic, COMET_MAGIC, sizeof (COMET_MAGIC)) != 0)
    {
      DBG (10, "convert_pic: error: file %s is not in COMET format\n",
	   base_name);
      fclose (ifp);
      return -1;
    }

  if (fread (pic, LOW_CAMERA_HEADER, 1, ifp) != 1)
    {
      DBG (10, "convert_pic: error: cannot read camera header\n");
      fclose (ifp);
      return -1;
    }

  res = pic[4];
  if (res == 0)
    {


      if (fread (pic + LOW_CAMERA_HEADER, LOW_CAMERA_HEADER, 1, ifp) != 1)
	{
	  DBG (10,
	       "convert_pic: error: cannot resync with high resolution header\n");
	  fclose (ifp);
	  return -1;
	}
    }

  if (fread (pic + CAMERA_HEADER (res), WIDTH (res), HEIGHT, ifp) != HEIGHT)
    {
      DBG (9, "convert_pic: error: cannot read picture\n");
      fclose (ifp);
      return -1;
    }

  fclose (ifp);


  image_size = IMAGE_SIZE (res);
  image_width = WIDTH (res);
  net_width = image_width - LEFT_MARGIN - RIGHT_MARGIN (res);
  camera_header = CAMERA_HEADER (res);
  components = (format & SAVE_24BITS) ? 3 : 1;


  if ((pp =
       alloc_pixmap (net_width - 1, HEIGHT - BOTTOM_MARGIN - 1,
		     components)) == NULL)
    {
      DBG (1, "convert_pic: error: alloc_pixmap\n");
      return -1;
    }

  comet_to_pixmap (pic, pp);

  if (format & SAVE_ADJASPECT)
    {


      if (res)
	pp2 = alloc_pixmap (320, HEIGHT - BOTTOM_MARGIN - 1, components);
      else
	pp2 = alloc_pixmap (net_width - 1, 373, components);

      if (pp2 == NULL)
	{
	  DBG (2, "convert_pic: error: alloc_pixmap\n");
	  free_pixmap (pp);
	  return -1;
	}

      if (res)
	zoom_x (pp, pp2);
      else
	zoom_y (pp, pp2);

      free_pixmap (pp);
      pp = pp2;
      pp2 = NULL;

    }

  return 0;
}
