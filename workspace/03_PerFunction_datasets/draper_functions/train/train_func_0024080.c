read_sleb128 (bfd_byte **iter, bfd_byte *end, bfd_signed_vma *value)
{
  bfd_byte *start, *p;

  start = *iter;
  if (!skip_leb128 (iter, end))
    return FALSE;

  p = *iter;
  *value = ((*--p & 0x7f) ^ 0x40) - 0x40;
  while (p > start)
    *value = (*value << 7) | (*--p & 0x7f);

  return TRUE;
}
