_bfd_generic_set_section_contents (bfd *abfd,
				   sec_ptr section,
				   const void *location,
				   file_ptr offset,
				   bfd_size_type count)
{
  if (count == 0)
    return TRUE;

  if (bfd_seek (abfd, section->filepos + offset, SEEK_SET) != 0
      || bfd_bwrite (location, count, abfd) != count)
    return FALSE;

  return TRUE;
}
