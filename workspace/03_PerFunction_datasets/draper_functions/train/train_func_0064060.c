byte_buffer_set_position (ByteBuffer *buffer, size_t position,
                               ElvinError *error)
{
  if (buffer->position != position)
  {
    if (byte_buffer_ensure_capacity (buffer, position, error))
    {
      buffer->position = position;

      return true;
    } else
    {
      return false;
    }
  }

  return true;
}
