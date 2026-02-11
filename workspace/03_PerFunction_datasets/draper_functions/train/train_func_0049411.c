get_current_line(OUTPUTHISTORY *h)
{
  z_ucs *last_stored_char_index, *last_newline_index, *result;
  size_t len, backlen=0, frontlen=0;
  bool wrap_encountered, has_wrapped = false;


  if ((last_stored_char_index = decrement_buffer_pointer(
          h,
          h->z_history_buffer_front_index,
          &has_wrapped)) == NULL)
  {
    TRACE_LOG("no current line: can't dec ptr.\n");
    return NULL;
  }

  last_newline_index = find_older_paragraph(h, last_stored_char_index);

  if (last_newline_index == NULL)
  {
    TRACE_LOG("already at last paragraph.\n");
    return NULL;
  }

  wrap_encountered
    = last_newline_index > h->z_history_buffer_front_index
    ? true
    : false;

  if (wrap_encountered == false)
    len = h->z_history_buffer_front_index - last_newline_index;
  else
  {
    backlen = h->z_history_buffer_end - last_newline_index;
    frontlen = h->z_history_buffer_front_index - h->z_history_buffer_start + 1;
    len = backlen + frontlen;
  }

  TRACE_LOG("cl-len: %ld (%ld + %ld), wrap: %d\n",
      (long int)len, (long int)backlen, (long int)frontlen, wrap_encountered);

  result = fizmo_malloc(sizeof(z_ucs) * (len + 1));

  if (wrap_encountered == false)
  {
    z_ucs_ncpy(result, last_newline_index, len);
  }
  else
  {
    z_ucs_ncpy(result, last_newline_index + 1, backlen);
    z_ucs_ncpy(result+backlen, h->z_history_buffer_start, frontlen);
  }

  result[len] = 0;

  return result;
}
