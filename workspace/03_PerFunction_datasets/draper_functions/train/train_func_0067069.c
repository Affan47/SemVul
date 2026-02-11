skip_atom (MoovRecovFile * moovrf, guint32 expected_fourcc)
{
  guint32 size;
  guint32 fourcc;

  if (!read_atom_header (moovrf->file, &fourcc, &size))
    return FALSE;
  if (fourcc != expected_fourcc)
    return FALSE;

  return (fseek (moovrf->file, size - 8, SEEK_CUR) == 0);
}
