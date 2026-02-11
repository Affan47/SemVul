atom_tfra_copy_data (AtomTFRA * tfra, guint8 ** buffer, guint64 * size,
    guint64 * offset)
{
  guint64 original_offset = *offset;
  guint32 i;
  TFRAEntry *entry;
  guint32 data;
  guint bytes;
  guint version;

  if (!atom_full_copy_data (&tfra->header, buffer, size, offset)) {
    return 0;
  }

  prop_copy_uint32 (tfra->track_ID, buffer, size, offset);
  prop_copy_uint32 (tfra->lengths, buffer, size, offset);
  prop_copy_uint32 (atom_array_get_len (&tfra->entries), buffer, size, offset);

  version = tfra->header.version;
  for (i = 0; i < atom_array_get_len (&tfra->entries); ++i) {
    entry = &atom_array_index (&tfra->entries, i);
    if (version) {
      prop_copy_uint64 (entry->time, buffer, size, offset);
      prop_copy_uint64 (entry->moof_offset, buffer, size, offset);
    } else {
      prop_copy_uint32 (entry->time, buffer, size, offset);
      prop_copy_uint32 (entry->moof_offset, buffer, size, offset);
    }

    bytes = (tfra->lengths & (0x3 << 4)) + 1;
    data = GUINT32_TO_BE (entry->traf_number);
    prop_copy_fixed_size_string (((guint8 *) & data) + 4 - bytes, bytes,
        buffer, size, offset);

    bytes = (tfra->lengths & (0x3 << 2)) + 1;
    data = GUINT32_TO_BE (entry->trun_number);
    prop_copy_fixed_size_string (((guint8 *) & data) + 4 - bytes, bytes,
        buffer, size, offset);

    bytes = (tfra->lengths & (0x3)) + 1;
    data = GUINT32_TO_BE (entry->sample_number);
    prop_copy_fixed_size_string (((guint8 *) & data) + 4 - bytes, bytes,
        buffer, size, offset);

  }

  atom_write_size (buffer, size, offset, original_offset);
  return *offset - original_offset;
}
