hb_buffer_ensure (hb_buffer_t *buffer, unsigned int size)
{
  unsigned int new_allocated = buffer->allocated;

  if (size > new_allocated)
  {
    while (size > new_allocated)
      new_allocated += (new_allocated >> 1) + 8;

    if (buffer->positions)
      buffer->positions = realloc (buffer->positions, new_allocated * sizeof (buffer->positions[0]));

    if (buffer->out_string != buffer->in_string)
    {
      buffer->in_string = realloc (buffer->in_string, new_allocated * sizeof (buffer->in_string[0]));
      buffer->out_string = (hb_internal_glyph_info_t *) buffer->positions;
    }
    else
    {
      buffer->in_string = realloc (buffer->in_string, new_allocated * sizeof (buffer->in_string[0]));
      buffer->out_string = buffer->in_string;
    }

    buffer->allocated = new_allocated;
  }
}
