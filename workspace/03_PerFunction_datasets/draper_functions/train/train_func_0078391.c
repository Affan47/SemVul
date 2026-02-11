separate_debug_file_exists (const char *name, const unsigned long crc)
{
  static unsigned char buffer [8 * 1024];
  unsigned long file_crc = 0;
  FILE *f;
  bfd_size_type count;

  BFD_ASSERT (name);

  f = real_fopen (name, FOPEN_RB);
  if (f == NULL)
    return FALSE;

  while ((count = fread (buffer, 1, sizeof (buffer), f)) > 0)
    file_crc = bfd_calc_gnu_debuglink_crc32 (file_crc, buffer, count);

  fclose (f);

  return crc == file_crc;
}
