size_of_aranges (void)
{
  unsigned long size;

  size = DWARF_ARANGES_HEADER_SIZE;


  if (text_section_used)
    size += 2 * DWARF2_ADDR_SIZE;
  if (cold_text_section_used)
    size += 2 * DWARF2_ADDR_SIZE;
  if (have_multiple_function_sections)
    {
      unsigned fde_idx = 0;

      for (fde_idx = 0; fde_idx < fde_table_in_use; fde_idx++)
	{
	  dw_fde_ref fde = &fde_table[fde_idx];

	  if (!fde->in_std_section)
	    size += 2 * DWARF2_ADDR_SIZE;
	  if (fde->dw_fde_second_begin && !fde->second_in_std_section)
	    size += 2 * DWARF2_ADDR_SIZE;
	}
    }


  size += 2 * DWARF2_ADDR_SIZE;
  return size;
}
