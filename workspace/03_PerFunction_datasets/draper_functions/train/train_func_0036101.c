HaveMessage()
{

  size_t r;
  if( H_LEN <= in_buffer.Count() ){
    r = get_nl(in_buffer.BasePointer());
    if( cfg_max_slice_size + H_LEN + H_PIECE_LEN < r )
      return -1;
    if( r + H_LEN <= in_buffer.Count() ) return 1;
  }
  return 0;
}
