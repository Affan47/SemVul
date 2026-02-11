PeekMessage(char m)
{
  return ( H_LEN < in_buffer.Count() && m == in_buffer.BasePointer()[H_LEN] &&
           get_nl(in_buffer.BasePointer()) ) ? 1 : 0;
}
