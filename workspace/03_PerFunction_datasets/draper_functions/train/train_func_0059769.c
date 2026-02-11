init_reloc_cookie (struct elf_reloc_cookie *cookie,
		   struct bfd_link_info *info, bfd *abfd)
{
  Elf_Internal_Shdr *symtab_hdr;
  const struct elf_backend_data *bed;

  bed = get_elf_backend_data (abfd);
  symtab_hdr = &elf_tdata (abfd)->symtab_hdr;

  cookie->abfd = abfd;
  cookie->sym_hashes = elf_sym_hashes (abfd);
  cookie->bad_symtab = elf_bad_symtab (abfd);
  if (cookie->bad_symtab)
    {
      cookie->locsymcount = symtab_hdr->sh_size / bed->s->sizeof_sym;
      cookie->extsymoff = 0;
    }
  else
    {
      cookie->locsymcount = symtab_hdr->sh_info;
      cookie->extsymoff = symtab_hdr->sh_info;
    }

  if (bed->s->arch_size == 32)
    cookie->r_sym_shift = 8;
  else
    cookie->r_sym_shift = 32;

  cookie->locsyms = (Elf_Internal_Sym *) symtab_hdr->contents;
  if (cookie->locsyms == NULL && cookie->locsymcount != 0)
    {
      cookie->locsyms = bfd_elf_get_elf_syms (abfd, symtab_hdr,
					      cookie->locsymcount, 0,
					      NULL, NULL, NULL);
      if (cookie->locsyms == NULL)
	{
	  info->callbacks->einfo (_("%P%X: can not read symbols: %E\n"));
	  return FALSE;
	}
      if (info->keep_memory)
	symtab_hdr->contents = (bfd_byte *) cookie->locsyms;
    }
  return TRUE;
}
