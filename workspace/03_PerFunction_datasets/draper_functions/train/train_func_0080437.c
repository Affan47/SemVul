output_aranges (unsigned long aranges_length)
{
  unsigned i;

  if (DWARF_INITIAL_LENGTH_SIZE - DWARF_OFFSET_SIZE == 4)
    dw2_asm_output_data (4, 0xffffffff,
      "Initial length escape value indicating 64-bit DWARF extension");
  dw2_asm_output_data (DWARF_OFFSET_SIZE, aranges_length,
		       "Length of Address Ranges Info");

  dw2_asm_output_data (2, 2, "DWARF Version");
  dw2_asm_output_offset (DWARF_OFFSET_SIZE, debug_info_section_label,
			 debug_info_section,
			 "Offset of Compilation Unit Info");
  dw2_asm_output_data (1, DWARF2_ADDR_SIZE, "Size of Address");
  dw2_asm_output_data (1, 0, "Size of Segment Descriptor");


  if (DWARF_ARANGES_PAD_SIZE)
    {


      dw2_asm_output_data (2, 0, "Pad to %d byte boundary",
			   2 * DWARF2_ADDR_SIZE);
      for (i = 2; i < (unsigned) DWARF_ARANGES_PAD_SIZE; i += 2)
	dw2_asm_output_data (2, 0, NULL);
    }


  if (text_section_used)
    {
      dw2_asm_output_addr (DWARF2_ADDR_SIZE, text_section_label, "Address");
      dw2_asm_output_delta (DWARF2_ADDR_SIZE, text_end_label,
			    text_section_label, "Length");
    }
  if (cold_text_section_used)
    {
      dw2_asm_output_addr (DWARF2_ADDR_SIZE, cold_text_section_label,
			   "Address");
      dw2_asm_output_delta (DWARF2_ADDR_SIZE, cold_end_label,
			    cold_text_section_label, "Length");
    }

  if (have_multiple_function_sections)
    {
      unsigned fde_idx;
      dw_fde_ref fde;

      FOR_EACH_VEC_ELT (dw_fde_ref, fde_vec, fde_idx, fde)
	{
	  if (!fde->in_std_section)
	    {
	      dw2_asm_output_addr (DWARF2_ADDR_SIZE, fde->dw_fde_begin,
				   "Address");
	      dw2_asm_output_delta (DWARF2_ADDR_SIZE, fde->dw_fde_end,
				    fde->dw_fde_begin, "Length");
	    }
	  if (fde->dw_fde_second_begin && !fde->second_in_std_section)
	    {
	      dw2_asm_output_addr (DWARF2_ADDR_SIZE, fde->dw_fde_second_begin,
				   "Address");
	      dw2_asm_output_delta (DWARF2_ADDR_SIZE, fde->dw_fde_second_end,
				    fde->dw_fde_second_begin, "Length");
	    }
	}
    }


  dw2_asm_output_data (DWARF2_ADDR_SIZE, 0, NULL);
  dw2_asm_output_data (DWARF2_ADDR_SIZE, 0, NULL);
}
