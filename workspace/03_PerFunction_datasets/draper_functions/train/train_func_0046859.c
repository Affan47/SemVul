hb_form_clusters (hb_buffer_t *buffer)
{
  unsigned int count;

  count = buffer->in_length;
  for (buffer->in_pos = 1; buffer->in_pos < count; buffer->in_pos++)
    if (buffer->unicode->get_general_category (IN_CURGLYPH()) == HB_CATEGORY_NON_SPACING_MARK)
      IN_CLUSTER (buffer->in_pos) = IN_CLUSTER (buffer->in_pos - 1);
}
