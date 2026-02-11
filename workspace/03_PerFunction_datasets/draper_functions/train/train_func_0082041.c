bgav_qt_stco_read_64(qt_atom_header_t * h,
                         bgav_input_context_t * input, qt_stco_t * ret)
  {
  uint32_t i;
  READ_VERSION_AND_FLAGS;
  memcpy(&ret->h, h, sizeof(*h));

  if(!bgav_input_read_32_be(input, &ret->num_entries))
    return 0;

  ret->entries = calloc(ret->num_entries, sizeof(*(ret->entries)));
  for(i = 0; i < ret->num_entries; i++)
    {
    if(!bgav_input_read_64_be(input, &ret->entries[i]))
      return 0;
    }
  return 1;
  }
