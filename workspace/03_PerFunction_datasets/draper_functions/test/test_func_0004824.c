get_64bit_elf_symbols (FILE * file,
		       Elf_Internal_Shdr * section,
		       unsigned long * num_syms_return)
{
  unsigned long number = 0;
  Elf64_External_Sym * esyms = NULL;
  Elf_External_Sym_Shndx * shndx = NULL;
  Elf_Internal_Sym * isyms = NULL;
  Elf_Internal_Sym * psym;
  unsigned int j;


  if (section->sh_entsize == 0)
    {
      error (_("sh_entsize is zero\n"));
      goto exit_point;
    }

  number = section->sh_size / section->sh_entsize;

  if (number * sizeof (Elf64_External_Sym) > section->sh_size + 1)
    {
      error (_("Invalid sh_entsize\n"));
      goto exit_point;
    }

  esyms = (Elf64_External_Sym *) get_data (NULL, file, section->sh_offset, 1,
                                           section->sh_size, _("symbols"));
  if (!esyms)
    goto exit_point;

  if (symtab_shndx_hdr != NULL
      && (symtab_shndx_hdr->sh_link
	  == (unsigned long) (section - section_headers)))
    {
      shndx = (Elf_External_Sym_Shndx *) get_data (NULL, file,
                                                   symtab_shndx_hdr->sh_offset,
                                                   1, symtab_shndx_hdr->sh_size,
                                                   _("symbol table section indicies"));
      if (shndx == NULL)
	goto exit_point;
    }

  isyms = (Elf_Internal_Sym *) cmalloc (number, sizeof (Elf_Internal_Sym));

  if (isyms == NULL)
    {
      error (_("Out of memory\n"));
      goto exit_point;
    }

  for (j = 0, psym = isyms; j < number; j++, psym++)
    {
      psym->st_name  = BYTE_GET (esyms[j].st_name);
      psym->st_info  = BYTE_GET (esyms[j].st_info);
      psym->st_other = BYTE_GET (esyms[j].st_other);
      psym->st_shndx = BYTE_GET (esyms[j].st_shndx);

      if (psym->st_shndx == (SHN_XINDEX & 0xffff) && shndx != NULL)
	psym->st_shndx
	  = byte_get ((unsigned char *) &shndx[j], sizeof (shndx[j]));
      else if (psym->st_shndx >= (SHN_LORESERVE & 0xffff))
	psym->st_shndx += SHN_LORESERVE - (SHN_LORESERVE & 0xffff);

      psym->st_value = BYTE_GET (esyms[j].st_value);
      psym->st_size  = BYTE_GET (esyms[j].st_size);
    }

 exit_point:
  if (shndx != NULL)
    free (shndx);
  if (esyms != NULL)
    free (esyms);

  if (num_syms_return != NULL)
    * num_syms_return = isyms == NULL ? 0 : number;

  return isyms;
}
