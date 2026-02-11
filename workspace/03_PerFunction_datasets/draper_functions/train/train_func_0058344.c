atom_tag_data_copy_data (AtomTagData * data, guint8 ** buffer, guint64 * size,
    guint64 * offset)
{
  guint64 original_offset = *offset;

  if (!atom_full_copy_data (&data->header, buffer, size, offset)) {
    return 0;
  }

  prop_copy_uint32 (data->reserved, buffer, size, offset);
  prop_copy_uint8_array (data->data, data->datalen, buffer, size, offset);

  atom_write_size (buffer, size, offset, original_offset);
  return *offset - original_offset;
}
