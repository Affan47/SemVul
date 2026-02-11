create_colorindex (j_decompress_ptr cinfo)
{
  my_cquantize_ptr cquantize = (my_cquantize_ptr) cinfo->cquantize;
  JSAMPROW indexptr;
  int i,j,k, nci, blksize, val, pad;


  if (cinfo->dither_mode == JDITHER_ORDERED) {
    pad = MAXJSAMPLE*2;
    cquantize->is_padded = TRUE;
  } else {
    pad = 0;
    cquantize->is_padded = FALSE;
  }

  cquantize->colorindex = (*cinfo->mem->alloc_sarray)
    ((j_common_ptr) cinfo, JPOOL_IMAGE,
     (JDIMENSION) (MAXJSAMPLE+1 + pad),
     (JDIMENSION) cinfo->out_color_components);


  blksize = cquantize->sv_actual;

  for (i = 0; i < cinfo->out_color_components; i++) {

    nci = cquantize->Ncolors[i];
    blksize = blksize / nci;


    if (pad)
      cquantize->colorindex[i] += MAXJSAMPLE;


    indexptr = cquantize->colorindex[i];
    val = 0;
    k = largest_input_value(cinfo, i, 0, nci-1);
    for (j = 0; j <= MAXJSAMPLE; j++) {
      while (j > k)
	k = largest_input_value(cinfo, i, ++val, nci-1);

      indexptr[j] = (JSAMPLE) (val * blksize);
    }

    if (pad)
      for (j = 1; j <= MAXJSAMPLE; j++) {
	indexptr[-j] = indexptr[0];
	indexptr[MAXJSAMPLE+j] = indexptr[MAXJSAMPLE];
      }
  }
}
