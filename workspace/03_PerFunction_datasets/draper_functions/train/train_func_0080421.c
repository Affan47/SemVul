get_archive_member_name_at (struct archive_info *arch,
                            unsigned long offset,
			    struct archive_info *nested_arch)
{
  size_t got;

  if (fseek (arch->file, offset, SEEK_SET) != 0)
    {
      error (_("%s: failed to seek to next file name\n"), arch->file_name);
      return NULL;
    }
  got = fread (&arch->arhdr, 1, sizeof arch->arhdr, arch->file);
  if (got != sizeof arch->arhdr)
    {
      error (_("%s: failed to read archive header\n"), arch->file_name);
      return NULL;
    }
  if (memcmp (arch->arhdr.ar_fmag, ARFMAG, 2) != 0)
    {
      error (_("%s: did not find a valid archive header\n"),
	     arch->file_name);
      return NULL;
    }

  return get_archive_member_name (arch, nested_arch);
}
