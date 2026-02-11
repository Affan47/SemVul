bfd_elf_gc_common_finalize_got_offsets (bfd *abfd,
					struct bfd_link_info *info)
{
  bfd *i;
  const struct elf_backend_data *bed = get_elf_backend_data (abfd);
  bfd_vma gotoff;
  struct alloc_got_off_arg gofarg;

  BFD_ASSERT (abfd == info->output_bfd);

  if (! is_elf_hash_table (info->hash))
    return FALSE;


  if (bed->want_got_plt)
    gotoff = 0;
  else
    gotoff = bed->got_header_size;


  for (i = info->input_bfds; i; i = i->link_next)
    {
      bfd_signed_vma *local_got;
      bfd_size_type j, locsymcount;
      Elf_Internal_Shdr *symtab_hdr;

      if (bfd_get_flavour (i) != bfd_target_elf_flavour)
	continue;

      local_got = elf_local_got_refcounts (i);
      if (!local_got)
	continue;

      symtab_hdr = &elf_tdata (i)->symtab_hdr;
      if (elf_bad_symtab (i))
	locsymcount = symtab_hdr->sh_size / bed->s->sizeof_sym;
      else
	locsymcount = symtab_hdr->sh_info;

      for (j = 0; j < locsymcount; ++j)
	{
	  if (local_got[j] > 0)
	    {
	      local_got[j] = gotoff;
	      gotoff += bed->got_elt_size (abfd, info, NULL, i, j);
	    }
	  else
	    local_got[j] = (bfd_vma) -1;
	}
    }


  gofarg.gotoff = gotoff;
  gofarg.info = info;
  elf_link_hash_traverse (elf_hash_table (info),
			  elf_gc_allocate_got_offsets,
			  &gofarg);
  return TRUE;
}
