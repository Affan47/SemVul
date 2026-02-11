bfd_cache_init (abfd)
     bfd *abfd;
{
  BFD_ASSERT (abfd->iostream != NULL);
  if (open_files >= BFD_CACHE_MAX_OPEN)
    {
      if (! close_one ())
	return FALSE;
    }
  insert (abfd);
  ++open_files;
  return TRUE;
}
