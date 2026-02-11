finish_output_pass (j_decompress_ptr cinfo)
{
  my_master_ptr master = (my_master_ptr) cinfo->master;

  if (cinfo->quantize_colors)
    (*cinfo->cquantize->finish_pass) (cinfo);
  master->pass_number++;
}
