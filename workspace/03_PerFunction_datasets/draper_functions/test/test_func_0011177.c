tekhex_object_p (bfd *abfd)
{
  char b[4];

  tekhex_init ();

  if (bfd_seek (abfd, (file_ptr) 0, SEEK_SET) != 0
      || bfd_bread (b, (bfd_size_type) 4, abfd) != 4)
    return NULL;

  if (b[0] != '%' || !ISHEX (b[1]) || !ISHEX (b[2]) || !ISHEX (b[3]))
    return NULL;

  tekhex_mkobject (abfd);

  if (!pass_over (abfd, first_phase))
    return NULL;

  return abfd->xvec;
}
