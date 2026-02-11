gg_image_write_to_bin_hdr_by_strip (const gGraphStripImagePtr img,
				    int *progress)
{

    FILE *out = img->file_handle;
    struct grid_codec_data *grid_codec =
	(struct grid_codec_data *) (img->codec_data);
    int row;
    int col;
    short *p_in_int16;
    int *p_in_int32;
    unsigned char *p_out;
    size_t sz;
    int endian_arch = gg_endian_arch ();

    for (row = 0; row < img->current_available_rows; row++)
      {
	  switch (img->bits_per_sample)
	    {
	    case 16:
		p_in_int16 = (short *) (img->pixels);
		p_in_int16 += row * img->width;
		sz = img->width * sizeof (short);
		break;
	    case 32:
		p_in_int32 = (int *) (img->pixels);
		p_in_int32 += row * img->width;
		sz = img->width * sizeof (int);
		break;
	    };
	  p_out = grid_codec->grid_buffer;

	  for (col = 0; col < img->width; col++)
	    {
		switch (img->bits_per_sample)
		  {
		  case 16:
		      if (*p_in_int16 < img->min_value)
			  img->min_value = *p_in_int16;
		      if (*p_in_int16 > img->max_value)
			  img->max_value = *p_in_int16;
		      gg_export_int16 (*p_in_int16++, p_out, 1, endian_arch);
		      p_out += sizeof (short);
		      break;
		  case 32:
		      if (*p_in_int32 < img->min_value)
			  img->min_value = *p_in_int32;
		      if (*p_in_int32 > img->max_value)
			  img->max_value = *p_in_int32;
		      gg_export_int32 (*p_in_int32++, p_out, 1, endian_arch);
		      p_out += sizeof (int);
		      break;
		  };
	    }

	  if (fwrite (grid_codec->grid_buffer, 1, sz, out) != sz)
	      return GGRAPH_BIN_CODEC_ERROR;
      }
    img->next_row += img->current_available_rows;

    if (progress != NULL)
	*progress =
	    (int) (((double) (img->next_row + 1) * 100.0) /
		   (double) (img->height));
    return GGRAPH_OK;
}
