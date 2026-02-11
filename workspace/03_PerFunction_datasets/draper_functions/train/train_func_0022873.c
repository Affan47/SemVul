elf_link_adjust_relocs (bfd *abfd,
			struct bfd_elf_section_reloc_data *reldata)
{
  unsigned int i;
  const struct elf_backend_data *bed = get_elf_backend_data (abfd);
  bfd_byte *erela;
  void (*swap_in) (bfd *, const bfd_byte *, Elf_Internal_Rela *);
  void (*swap_out) (bfd *, const Elf_Internal_Rela *, bfd_byte *);
  bfd_vma r_type_mask;
  int r_sym_shift;
  unsigned int count = reldata->count;
  struct elf_link_hash_entry **rel_hash = reldata->hashes;

  if (reldata->hdr->sh_entsize == bed->s->sizeof_rel)
    {
      swap_in = bed->s->swap_reloc_in;
      swap_out = bed->s->swap_reloc_out;
    }
  else if (reldata->hdr->sh_entsize == bed->s->sizeof_rela)
    {
      swap_in = bed->s->swap_reloca_in;
      swap_out = bed->s->swap_reloca_out;
    }
  else
    abort ();

  if (bed->s->int_rels_per_ext_rel > MAX_INT_RELS_PER_EXT_REL)
    abort ();

  if (bed->s->arch_size == 32)
    {
      r_type_mask = 0xff;
      r_sym_shift = 8;
    }
  else
    {
      r_type_mask = 0xffffffff;
      r_sym_shift = 32;
    }

  erela = reldata->hdr->contents;
  for (i = 0; i < count; i++, rel_hash++, erela += reldata->hdr->sh_entsize)
    {
      Elf_Internal_Rela irela[MAX_INT_RELS_PER_EXT_REL];
      unsigned int j;

      if (*rel_hash == NULL)
	continue;

      BFD_ASSERT ((*rel_hash)->indx >= 0);

      (*swap_in) (abfd, erela, irela);
      for (j = 0; j < bed->s->int_rels_per_ext_rel; j++)
	irela[j].r_info = ((bfd_vma) (*rel_hash)->indx << r_sym_shift
			   | (irela[j].r_info & r_type_mask));
      (*swap_out) (abfd, irela, erela);
    }
}
