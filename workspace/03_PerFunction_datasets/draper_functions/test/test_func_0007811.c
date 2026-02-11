output_compilation_unit_header (void)
{
  int ver = dwarf_version;

  if (DWARF_INITIAL_LENGTH_SIZE - DWARF_OFFSET_SIZE == 4)
    dw2_asm_output_data (4, 0xffffffff,
      "Initial length escape value indicating 64-bit DWARF extension");
  dw2_asm_output_data (DWARF_OFFSET_SIZE,
		       next_die_offset - DWARF_INITIAL_LENGTH_SIZE,
		       "Length of Compilation Unit Info");
  dw2_asm_output_data (2, ver, "DWARF version number");
  dw2_asm_output_offset (DWARF_OFFSET_SIZE, abbrev_section_label,
			 debug_abbrev_section,
			 "Offset Into Abbrev. Section");
  dw2_asm_output_data (1, DWARF2_ADDR_SIZE, "Pointer Size (in bytes)");
}
