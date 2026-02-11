atk_text_range_copy (AtkTextRange *src)
{
  AtkTextRange *dst = g_new0 (AtkTextRange, 1);
  dst->bounds = src->bounds;
  dst->start_offset = src->start_offset;
  dst->end_offset = src->end_offset;
  if (src->content)
    dst->content = g_strdup (src->content);
  return dst;
}
