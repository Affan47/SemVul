packed_col_length(const uchar *data_ptr, uint length)
{
  if (length > 255)
    return uint2korr(data_ptr)+2;
  return (uint) *data_ptr + 1;
}
