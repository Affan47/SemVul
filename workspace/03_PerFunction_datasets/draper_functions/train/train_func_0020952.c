get_huffman_decoder_configuration(j_decompress_ptr cinfo,
        huffman_offset_data *offset)
{
  int i;
  phuff_entropy_ptr entropy = (phuff_entropy_ptr) cinfo->entropy;
  jpeg_get_huffman_decoder_configuration_progressive(cinfo, offset);
  offset->EOBRUN = entropy->saved.EOBRUN;
  for (i = 0; i < cinfo->comps_in_scan; i++)
    offset->prev_dc[i] = entropy->saved.last_dc_val[i];
}
