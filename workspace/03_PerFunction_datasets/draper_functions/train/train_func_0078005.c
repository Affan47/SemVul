find_source_reloc (source_reloc *src_relocs,
		   int src_count,
		   asection *sec,
		   Elf_Internal_Rela *irel)
{
  int i;

  for (i = 0; i < src_count; i++)
    {
      if (src_relocs[i].source_sec == sec
	  && src_relocs[i].r_rel.rela.r_offset == irel->r_offset
	  && (ELF32_R_TYPE (src_relocs[i].r_rel.rela.r_info)
	      == ELF32_R_TYPE (irel->r_info)))
	return &src_relocs[i];
    }

  return NULL;
}
