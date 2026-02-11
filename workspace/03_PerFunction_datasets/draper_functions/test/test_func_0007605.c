_bfd_elf_new_section_hook (bfd *abfd, asection *sec)
{
  struct bfd_elf_section_data *sdata;
  const struct elf_backend_data *bed;
  const struct bfd_elf_special_section *ssect;

  sdata = (struct bfd_elf_section_data *) sec->used_by_bfd;
  if (sdata == NULL)
    {
      sdata = (struct bfd_elf_section_data *) bfd_zalloc (abfd,
                                                          sizeof (*sdata));
      if (sdata == NULL)
	return FALSE;
      sec->used_by_bfd = sdata;
    }


  bed = get_elf_backend_data (abfd);
  sec->use_rela_p = bed->default_use_rela_p;


  if (abfd->direction != read_direction
      || (sec->flags & SEC_LINKER_CREATED) != 0)
    {
      ssect = (*bed->get_sec_type_attr) (abfd, sec);
      if (ssect != NULL
	  && (!sec->flags
	      || (sec->flags & SEC_LINKER_CREATED) != 0
	      || ssect->type == SHT_INIT_ARRAY
	      || ssect->type == SHT_FINI_ARRAY))
	{
	  elf_section_type (sec) = ssect->type;
	  elf_section_flags (sec) = ssect->attr;
	}
    }

  return _bfd_generic_new_section_hook (abfd, sec);
}
