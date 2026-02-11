xg_find_narrowest_format (vliw_insn *vinsn)
{


  xtensa_isa isa = xtensa_default_isa;
  xtensa_format format;
  xtensa_opcode nop_opcode = xtensa_nop_opcode;

  if (vinsn->num_slots == 1)
    return xg_get_single_format (vinsn->slots[0].opcode);

  for (format = 0; format < xtensa_isa_num_formats (isa); format++)
    {
      vliw_insn v_copy;
      xg_copy_vinsn (&v_copy, vinsn);
      if (xtensa_format_num_slots (isa, format) == v_copy.num_slots)
	{
	  int slot;
	  int fit = 0;
	  for (slot = 0; slot < v_copy.num_slots; slot++)
	    {
	      if (v_copy.slots[slot].opcode == nop_opcode)
		{
		  v_copy.slots[slot].opcode =
		    xtensa_format_slot_nop_opcode (isa, format, slot);
		  v_copy.slots[slot].ntok = 0;
		}

	      if (opcode_fits_format_slot (v_copy.slots[slot].opcode,
					   format, slot))
		fit++;
	      else if (v_copy.num_slots > 1)
		{
		  TInsn widened;

		  if (!v_copy.slots[slot].keep_wide
		      && !v_copy.slots[slot].is_specific_opcode
		      && xg_is_single_relaxable_insn (&v_copy.slots[slot],
						      &widened, TRUE)
		      && opcode_fits_format_slot (widened.opcode,
						  format, slot))
		    {
		      v_copy.slots[slot] = widened;
		      fit++;
		    }
		}
	    }
	  if (fit == v_copy.num_slots)
	    {
	      xg_copy_vinsn (vinsn, &v_copy);
	      xtensa_format_encode (isa, format, vinsn->insnbuf);
	      vinsn->format = format;
	      break;
	    }
	}
    }

  if (format == xtensa_isa_num_formats (isa))
    return XTENSA_UNDEFINED;

  return format;
}
