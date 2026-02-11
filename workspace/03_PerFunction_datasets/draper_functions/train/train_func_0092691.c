output_range_list_offset (dw_attr_ref a)
{
  const char *name = dwarf_attr_name (a->dw_attr);

  if (a->dw_attr_val.val_entry == RELOCATED_OFFSET)
    {
      char *p = strchr (ranges_section_label, '\0');
      sprintf (p, "+" HOST_WIDE_INT_PRINT_HEX, a->dw_attr_val.v.val_offset);
      dw2_asm_output_offset (DWARF_OFFSET_SIZE, ranges_section_label,
                             debug_ranges_section, "%s", name);
      *p = '\0';
    }
  else
    dw2_asm_output_data (DWARF_OFFSET_SIZE, a->dw_attr_val.v.val_offset,
                         "%s (offset from %s)", name, ranges_section_label);
}
