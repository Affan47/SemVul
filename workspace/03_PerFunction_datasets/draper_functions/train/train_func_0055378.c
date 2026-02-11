read_color_map (j_decompress_ptr cinfo, FILE * infile)
{

  cinfo->colormap = (*cinfo->mem->alloc_sarray)
    ((j_common_ptr) cinfo, JPOOL_IMAGE,
     (JDIMENSION) (MAXJSAMPLE+1), (JDIMENSION) 3);
  cinfo->actual_number_of_colors = 0;


  switch (getc(infile)) {
  case 'G':
    read_gif_map(cinfo, infile);
    break;
  case 'P':
    read_ppm_map(cinfo, infile);
    break;
  default:
    ERREXIT(cinfo, JERR_BAD_CMAP_FILE);
    break;
  }
}
