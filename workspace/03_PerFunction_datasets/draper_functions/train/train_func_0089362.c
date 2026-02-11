skip_mem_input_data (oe_j_decompress_ptr cinfo, long num_bytes)
{
    nif_src_ptr src = (nif_src_ptr)cinfo->src;


  if (num_bytes > 0) {
    while (num_bytes > (int) src->pub.bytes_in_buffer) {
      num_bytes -= (int) src->pub.bytes_in_buffer;
      (void) fill_mem_input_buffer(cinfo);


    }
    src->pub.next_input_byte += (size_t) num_bytes;
    src->pub.bytes_in_buffer -= (size_t) num_bytes;
  }
}
