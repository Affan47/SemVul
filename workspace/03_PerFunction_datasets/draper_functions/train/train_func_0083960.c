elf64_ia64_add_symbol_hook (bfd *abfd,
			    struct bfd_link_info *info,
			    Elf_Internal_Sym *sym,
			    const char **namep ATTRIBUTE_UNUSED,
			    flagword *flagsp ATTRIBUTE_UNUSED,
			    asection **secp,
			    bfd_vma *valp)
{
  if (sym->st_shndx == SHN_COMMON
      && !info->relocatable
      && sym->st_size <= elf_gp_size (abfd))
    {


      asection *scomm = bfd_get_section_by_name (abfd, ".scommon");

      if (scomm == NULL)
	{
	  scomm = bfd_make_section_with_flags (abfd, ".scommon",
					       (SEC_ALLOC
						| SEC_IS_COMMON
						| SEC_LINKER_CREATED));
	  if (scomm == NULL)
	    return FALSE;
	}

      *secp = scomm;
      *valp = sym->st_size;
    }

  return TRUE;
}
