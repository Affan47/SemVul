input_identifier (struct data_in *data_in, struct lto_input_block *ib)
{
  unsigned int len;
  const char *ptr;

  ptr = streamer_read_indexed_string (data_in, ib, &len);
  if (!ptr)
    return NULL;
  return get_identifier_with_length (ptr, len);
}
