finish_output_gif (j_decompress_ptr cinfo, djpeg_dest_ptr dinfo)
{
  gif_dest_ptr dest = (gif_dest_ptr) dinfo;


  compress_term(dest);

  putc(0, dest->pub.output_file);

  putc(';', dest->pub.output_file);

  fflush(dest->pub.output_file);
  if (ferror(dest->pub.output_file))
    ERREXIT(cinfo, JERR_FILE_WRITE);
}
