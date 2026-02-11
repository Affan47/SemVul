do_fix_for_final_link (Elf_Internal_Rela *rel,
		       bfd *input_bfd,
		       asection *input_section,
		       bfd_byte *contents,
		       bfd_vma *relocationp)
{
  asection *sec;
  int r_type = ELF32_R_TYPE (rel->r_info);
  reloc_bfd_fix *fix;
  bfd_vma fixup_diff;

  if (r_type == R_XTENSA_NONE)
    return;

  fix = get_bfd_fix (input_section, rel->r_offset, r_type);
  if (!fix)
    return;

  sec = fix->target_sec;

  fixup_diff = rel->r_addend;
  if (elf_howto_table[fix->src_type].partial_inplace)
    {
      bfd_vma inplace_val;
      BFD_ASSERT (fix->src_offset
		  < bfd_get_section_limit (input_bfd, input_section));
      inplace_val = bfd_get_32 (input_bfd, &contents[fix->src_offset]);
      fixup_diff += inplace_val;
    }

  *relocationp = (sec->output_section->vma
		  + sec->output_offset
		  + fix->target_offset - fixup_diff);
}
