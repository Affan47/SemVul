get_32bit_row (j_compress_ptr cinfo, cjpeg_source_ptr sinfo)

{
  bmp_source_ptr source = (bmp_source_ptr) sinfo;
  JSAMPARRAY image_ptr;
  register JSAMPROW inptr, outptr;
  register JDIMENSION col;


  source->source_row--;
  image_ptr = (*cinfo->mem->access_virt_sarray)
    ((j_common_ptr) cinfo, source->whole_image,
     source->source_row, (JDIMENSION) 1, FALSE);


  inptr = image_ptr[0];
  outptr = source->pub.buffer[0];
  for (col = cinfo->image_width; col > 0; col--) {
    outptr[2] = *inptr++;
    outptr[1] = *inptr++;
    outptr[0] = *inptr++;
    inptr++;
    outptr += 3;
  }

  return 1;
}
