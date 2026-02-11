predict_start_pass (j_decompress_ptr cinfo)
{
  j_lossless_d_ptr losslsd = (j_lossless_d_ptr) cinfo->codec;
  int ci;


  if (cinfo->Ss < 1 || cinfo->Ss > 7 ||
      cinfo->Se != 0 || cinfo->Ah != 0 ||
      cinfo->Al > 15)
    ERREXIT4(cinfo, JERR_BAD_LOSSLESS,
       cinfo->Ss, cinfo->Se, cinfo->Ah, cinfo->Al);


  for (ci = 0; ci < cinfo->num_components; ci++)
    losslsd->predict_undifference[ci] = jpeg_undifference_first_row;
}
