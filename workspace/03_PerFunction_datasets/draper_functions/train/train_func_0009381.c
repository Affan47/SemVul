byte_buffer_write_int32 (ByteBuffer *buffer, int32_t value,
                              ElvinError *error)
{
  on_error_return_false
    (byte_buffer_ensure_capacity (buffer, buffer->position + 4, error));

  *(int32_t *)(buffer->data + buffer->position) = htonl (value);

  buffer->position += 4;

  return true;
}
