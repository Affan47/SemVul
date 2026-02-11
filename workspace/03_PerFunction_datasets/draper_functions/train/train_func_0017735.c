input_string (struct data_in *data_in, struct lto_input_block *ib)
{
  unsigned int len;
  const char *ptr;
  unsigned int is_null;

  is_null = lto_input_uleb128 (ib);
  if (is_null)
    return NULL;

  ptr = input_string_internal (data_in, ib, &len);
  if (ptr[len - 1] != '\0')
    internal_error ("bytecode stream: found non-null terminated string");

  return ptr;
}
