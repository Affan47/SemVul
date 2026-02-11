bfd_sections_find_if (bfd *abfd,
		      bfd_boolean (*operation) (bfd *, asection *, void *),
		      void *user_storage)
{
  asection *sect;

  for (sect = abfd->sections; sect != NULL; sect = sect->next)
    if ((*operation) (abfd, sect, user_storage))
      break;

  return sect;
}
