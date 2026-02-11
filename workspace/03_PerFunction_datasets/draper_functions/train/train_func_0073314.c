get_elf_r_symndx_hash_entry (bfd *abfd, unsigned long r_symndx)
{
  unsigned long indx;
  struct elf_link_hash_entry *h;
  Elf_Internal_Shdr *symtab_hdr = &elf_tdata (abfd)->symtab_hdr;

  if (r_symndx < symtab_hdr->sh_info)
    return NULL;

  indx = r_symndx - symtab_hdr->sh_info;
  h = elf_sym_hashes (abfd)[indx];
  while (h->root.type == bfd_link_hash_indirect
	 || h->root.type == bfd_link_hash_warning)
    h = (struct elf_link_hash_entry *) h->root.u.i.link;
  return h;
}
