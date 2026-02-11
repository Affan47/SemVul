find_older_paragraph(OUTPUTHISTORY *h, z_ucs *index)
{
  bool has_wrapped;

  if ( (h == NULL) || (h->z_history_buffer_size == 0) )
    return NULL;

  has_wrapped = (index == h->z_history_buffer_front_index ? false : true);

  while (*index != '\n')
    if ((index = decrement_buffer_pointer(h, index, &has_wrapped)) == NULL)
      return NULL;

  return index;
}
