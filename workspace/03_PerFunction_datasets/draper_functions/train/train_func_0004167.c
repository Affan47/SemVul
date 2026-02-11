strings_object_file (const char *file)
{
  filename_and_size_t filename_and_size;
  bfd *abfd;

  abfd = bfd_openr (file, target);

  if (abfd == NULL)

    return FALSE;


  if (!bfd_check_format (abfd, bfd_object))
    {
      bfd_close (abfd);
      return FALSE;
    }

  got_a_section = FALSE;
  filename_and_size.filename = file;
  filename_and_size.filesize = 0;
  bfd_map_over_sections (abfd, strings_a_section, & filename_and_size);

  if (!bfd_close (abfd))
    {
      bfd_nonfatal (file);
      return FALSE;
    }

  return got_a_section;
}
