bfd_get_section_by_name (bfd *abfd, const char *name)
{
  struct section_hash_entry *sh;

  sh = section_hash_lookup (&abfd->section_htab, name, FALSE, FALSE);
  if (sh != NULL)
    return &sh->section;

  return NULL;
}
