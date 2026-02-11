set_pltoff_entry (bfd *abfd, struct bfd_link_info *info,
		  struct elf64_ia64_dyn_sym_info *dyn_i,
		  bfd_vma value, bfd_boolean is_plt)
{
  struct elf64_ia64_link_hash_table *ia64_info;
  asection *pltoff_sec;

  ia64_info = elf64_ia64_hash_table (info);
  if (ia64_info == NULL)
    return 0;

  pltoff_sec = ia64_info->pltoff_sec;


  if ((! dyn_i->want_plt || is_plt)
      && !dyn_i->pltoff_done)
    {
      bfd_vma gp = _bfd_get_gp_value (abfd);


      bfd_put_64 (abfd, value, pltoff_sec->contents + dyn_i->pltoff_offset);
      bfd_put_64 (abfd, gp, pltoff_sec->contents + dyn_i->pltoff_offset + 8);


      if (!is_plt
	  && info->shared
	  && (!dyn_i->h
	      || ELF_ST_VISIBILITY (dyn_i->h->other) == STV_DEFAULT
	      || dyn_i->h->root.type != bfd_link_hash_undefweak))
	{
	  unsigned int dyn_r_type;

	  if (bfd_big_endian (abfd))
	    dyn_r_type = R_IA64_REL64MSB;
	  else
	    dyn_r_type = R_IA64_REL64LSB;

	  elf64_ia64_install_dyn_reloc (abfd, NULL, pltoff_sec,
					ia64_info->rel_pltoff_sec,
					dyn_i->pltoff_offset,
					dyn_r_type, 0, value);
	  elf64_ia64_install_dyn_reloc (abfd, NULL, pltoff_sec,
					ia64_info->rel_pltoff_sec,
					dyn_i->pltoff_offset + ARCH_SIZE / 8,
					dyn_r_type, 0, gp);
	}

      dyn_i->pltoff_done = 1;
    }


  value = (pltoff_sec->output_section->vma
	   + pltoff_sec->output_offset
	   + dyn_i->pltoff_offset);

  return value;
}
