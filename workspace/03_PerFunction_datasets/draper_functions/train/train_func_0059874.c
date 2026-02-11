perform_tiling (const image_t *image, tiling_t *tiling)


{
   if (tiling->exponent)
   {
      unsigned 	tiles = 1 << tiling->exponent;
      bool_t   *tile_valid;

      tiling->vorder = fiasco_calloc (tiles, sizeof (int));
      tile_valid     = fiasco_calloc (tiles, sizeof (bool_t));

      if (tiling->method == FIASCO_TILING_VARIANCE_ASC
	  || tiling->method == FIASCO_TILING_VARIANCE_DSC)
      {
	 unsigned    address;
	 unsigned    number;
	 unsigned    lx       = log2 (image->width - 1) + 1;
	 unsigned    ly       = log2 (image->height - 1) + 1;
	 unsigned    level    = max (lx, ly) * 2 - ((ly == lx + 1) ? 1 : 0);
	 var_list_t *var_list = fiasco_calloc (tiles, sizeof (var_list_t));


	 for (number = 0, address = 0; address < tiles; address++)
	 {
	    unsigned width, height;
	    unsigned x0, y0;

	    locate_subimage (level, level - tiling->exponent, address,
			     &x0, &y0, &width, &height);
	    if (x0 < image->width && y0 < image->height)
	    {
	       if (x0 + width > image->width)
		  width = image->width - x0;
	       if (y0 + height > image->height)
		  height = image->height - y0;

	       var_list [number].variance
		  = variance (image->pixels [GRAY], x0, y0,
			      width, height, image->width);
	       var_list [number].address  = address;
	       number++;
	       tile_valid [address] = YES;
	    }
	    else
	       tile_valid [address] = NO;
	 }


	 if (tiling->method == FIASCO_TILING_VARIANCE_DSC)
	    qsort (var_list, number, sizeof (var_list_t), cmpdecvar);
	 else
	    qsort (var_list, number, sizeof (var_list_t), cmpincvar);

	 for (number = 0, address = 0; address < tiles; address++)
	    if (tile_valid [address])
	    {
	       tiling->vorder [address] = var_list [number].address;
	       number++;
	       debug_message ("tile number %d has original address %d",
			      number, tiling->vorder [address]);
	    }
	    else
	       tiling->vorder [address] = -1;

	 fiasco_free (var_list);
      }
      else if (tiling->method == FIASCO_TILING_SPIRAL_DSC
	       || tiling->method == FIASCO_TILING_SPIRAL_ASC)
      {
	 compute_spiral (tiling->vorder, image->width, image->height,
			 tiling->exponent,
			 tiling->method == FIASCO_TILING_SPIRAL_ASC);
      }
      else
      {
	 warning ("Unsupported image tiling method.\n"
		  "Skipping image tiling step.");
	 tiling->exponent = 0;
      }
   }
}
