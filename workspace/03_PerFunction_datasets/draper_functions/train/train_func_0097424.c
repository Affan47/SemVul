output_attr_index_or_value (dw_attr_ref a)
{
  const char *name = dwarf_attr_name (a->dw_attr);

  if (dwarf_split_debug_info && AT_index (a) != NOT_INDEXED)
    {
      dw2_asm_output_data_uleb128 (AT_index (a), "%s", name);
      return;
    }
  switch (AT_class (a))
    {
      case dw_val_class_addr:
        dw2_asm_output_addr_rtx (DWARF2_ADDR_SIZE, AT_addr (a), "%s", name);
        break;
      case dw_val_class_high_pc:
      case dw_val_class_lbl_id:
        dw2_asm_output_addr (DWARF2_ADDR_SIZE, AT_lbl (a), "%s", name);
        break;
      case dw_val_class_loc_list:
        output_loc_list_offset (a);
        break;
      default:
        gcc_unreachable ();
    }
}
