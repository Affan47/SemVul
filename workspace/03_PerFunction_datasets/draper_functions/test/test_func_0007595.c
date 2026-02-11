adjust_bit_field_mem_for_reg (enum extraction_pattern pattern,
			      rtx op0, HOST_WIDE_INT bitsize,
			      HOST_WIDE_INT bitnum,
			      unsigned HOST_WIDE_INT bitregion_start,
			      unsigned HOST_WIDE_INT bitregion_end,
			      enum machine_mode fieldmode,
			      unsigned HOST_WIDE_INT *new_bitnum)
{
  bit_field_mode_iterator iter (bitsize, bitnum, bitregion_start,
				bitregion_end, MEM_ALIGN (op0),
				MEM_VOLATILE_P (op0));
  enum machine_mode best_mode;
  if (iter.next_mode (&best_mode))
    {


      if (!iter.prefer_smaller_modes ())
	{


	  enum machine_mode limit_mode = word_mode;
	  extraction_insn insn;
	  if (get_best_reg_extraction_insn (&insn, pattern,
					    GET_MODE_BITSIZE (best_mode),
					    fieldmode))
	    limit_mode = insn.field_mode;

	  enum machine_mode wider_mode;
	  while (iter.next_mode (&wider_mode)
		 && GET_MODE_SIZE (wider_mode) <= GET_MODE_SIZE (limit_mode))
	    best_mode = wider_mode;
	}
      return narrow_bit_field_mem (op0, best_mode, bitsize, bitnum,
				   new_bitnum);
    }
  return NULL_RTX;
}
