atspi_text_range_copy (AtspiTextRange *src)
{
  AtspiTextRange *dst = g_new (AtspiTextRange, 1);

  dst->content = g_strdup (src->content);
  dst->start_offset = src->start_offset;
  dst->end_offset = src->end_offset;
  return dst;
}
