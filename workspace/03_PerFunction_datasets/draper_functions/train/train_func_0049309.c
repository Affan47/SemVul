PeekMessage()
{
  return ( H_LEN < in_buffer.Count() && get_nl(in_buffer.BasePointer()) ) ?
           in_buffer.BasePointer()[H_LEN] : 0;
}
