atom_mfro_copy_data (guint32 s, guint8 ** buffer, guint64 * size,
    guint64 * offset)
{
  guint64 original_offset = *offset;
  guint8 flags[3] = { 0, 0, 0 };
  AtomFull mfro;

  atom_full_init (&mfro, FOURCC_mfro, 0, 0, 0, flags);

  if (!atom_full_copy_data (&mfro, buffer, size, offset)) {
    return 0;
  }

  prop_copy_uint32 (s, buffer, size, offset);

  atom_write_size (buffer, size, offset, original_offset);

  return *offset - original_offset;
}
