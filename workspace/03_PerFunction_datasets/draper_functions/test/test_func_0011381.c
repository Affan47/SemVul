check_section_ebb_pcrels_fit (bfd *abfd,
			      asection *sec,
			      bfd_byte *contents,
			      Elf_Internal_Rela *internal_relocs,
			      const ebb_constraint *constraint,
			      const xtensa_opcode *reloc_opcodes)
{
  unsigned i, j;
  Elf_Internal_Rela *irel;
  xlate_map_t *xmap = NULL;
  bfd_boolean ok = TRUE;
  xtensa_relax_info *relax_info;

  relax_info = get_xtensa_relax_info (sec);

  if (relax_info && sec->reloc_count > 100)
    {
      xmap = build_xlate_map (sec, relax_info);


    }

  for (i = 0; i < sec->reloc_count; i++)
    {
      r_reloc r_rel;
      bfd_vma orig_self_offset, orig_target_offset;
      bfd_vma self_offset, target_offset;
      int r_type;
      reloc_howto_type *howto;
      int self_removed_bytes, target_removed_bytes;

      irel = &internal_relocs[i];
      r_type = ELF32_R_TYPE (irel->r_info);

      howto = &elf_howto_table[r_type];


      if (r_type == R_XTENSA_ASM_SIMPLIFY
	  || r_type == R_XTENSA_32_PCREL
	  || !howto->pc_relative)
	continue;

      r_reloc_init (&r_rel, abfd, irel, contents,
		    bfd_get_section_limit (abfd, sec));

      if (r_reloc_get_section (&r_rel) != sec)
	continue;

      orig_self_offset = irel->r_offset;
      orig_target_offset = r_rel.target_offset;

      self_offset = orig_self_offset;
      target_offset = orig_target_offset;

      if (relax_info)
	{
	  self_offset =
	    xlate_offset_with_removed_text (xmap, &relax_info->action_list,
					    orig_self_offset);
	  target_offset =
	    xlate_offset_with_removed_text (xmap, &relax_info->action_list,
					    orig_target_offset);
	}

      self_removed_bytes = 0;
      target_removed_bytes = 0;

      for (j = 0; j < constraint->action_count; ++j)
	{
	  proposed_action *action = &constraint->actions[j];
	  bfd_vma offset = action->offset;
	  int removed_bytes = action->removed_bytes;
	  if (offset < orig_self_offset
	      || (offset == orig_self_offset && action->action == ta_fill
		  && action->removed_bytes < 0))
	    self_removed_bytes += removed_bytes;
	  if (offset < orig_target_offset
	      || (offset == orig_target_offset && action->action == ta_fill
		  && action->removed_bytes < 0))
	    target_removed_bytes += removed_bytes;
	}
      self_offset -= self_removed_bytes;
      target_offset -= target_removed_bytes;


      if (is_alt_relocation (ELF32_R_TYPE (irel->r_info)))
	{


	}
      else
	{
	  xtensa_opcode opcode;
	  int opnum;

	  if (reloc_opcodes)
	    opcode = reloc_opcodes[i];
	  else
	    opcode = get_relocation_opcode (abfd, sec, contents, irel);
	  if (opcode == XTENSA_UNDEFINED)
	    {
	      ok = FALSE;
	      break;
	    }

	  opnum = get_relocation_opnd (opcode, ELF32_R_TYPE (irel->r_info));
	  if (opnum == XTENSA_UNDEFINED)
	    {
	      ok = FALSE;
	      break;
	    }

	  if (!pcrel_reloc_fits (opcode, opnum, self_offset, target_offset))
	    {
	      ok = FALSE;
	      break;
	    }
	}
    }

  if (xmap)
    free_xlate_map (xmap);

  return ok;
}
