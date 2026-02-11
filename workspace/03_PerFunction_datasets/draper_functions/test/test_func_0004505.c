skip_bytes (bfd_byte **iter, bfd_byte *end, bfd_size_type length)
{
  if ((bfd_size_type) (end - *iter) < length)
    {
      *iter = end;
      return FALSE;
    }
  *iter += length;
  return TRUE;
}
