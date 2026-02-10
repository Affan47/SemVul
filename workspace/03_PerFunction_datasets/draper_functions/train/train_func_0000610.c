add_AT_lbl_id (dw_die_ref die, enum dwarf_attribute attr_kind,
               const char *lbl_id)
{
  dw_attr_node attr;

  attr.dw_attr = attr_kind;
  attr.dw_attr_val.val_class = dw_val_class_lbl_id;
  attr.dw_attr_val.val_entry = NULL;
  attr.dw_attr_val.v.val_lbl_id = xstrdup (lbl_id);
  if (dwarf_split_debug_info)
    attr.dw_attr_val.val_entry
        = add_addr_table_entry (attr.dw_attr_val.v.val_lbl_id,
                                ate_kind_label);
  add_dwarf_attr (die, &attr);
}
