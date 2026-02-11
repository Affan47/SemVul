byte_buffer_read_string (ByteBuffer *buffer, ElvinError *error)
{
  uint32_t length = byte_buffer_read_int32 (buffer, error);
  char *string;

  check_max_size (length, MAX_STRING_LENGTH, "String too long", error);

  if (!elvin_error_ok (error))
    return NULL;

  string = emalloc (length + 1);

  if (byte_buffer_read_bytes (buffer, (uint8_t *)string, length, error) &&
      byte_buffer_skip (buffer, padding_for (length), error))
  {
    string [length] = '\0';

    return string;
  } else
  {
    free (string);

    return NULL;
  }
}
