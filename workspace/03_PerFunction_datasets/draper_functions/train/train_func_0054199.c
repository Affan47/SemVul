gen_inheritance_die (tree binfo, tree access, dw_die_ref context_die)
{
  dw_die_ref die = new_die (DW_TAG_inheritance, context_die, binfo);

  add_type_attribute (die, BINFO_TYPE (binfo), 0, 0, context_die);
  add_data_member_location_attribute (die, binfo);

  if (BINFO_VIRTUAL_P (binfo))
    add_AT_unsigned (die, DW_AT_virtuality, DW_VIRTUALITY_virtual);


  if (access == access_public_node)
    {
      if (dwarf_version == 2
	  || context_die->die_tag == DW_TAG_class_type)
      add_AT_unsigned (die, DW_AT_accessibility, DW_ACCESS_public);
    }
  else if (access == access_protected_node)
    add_AT_unsigned (die, DW_AT_accessibility, DW_ACCESS_protected);
  else if (dwarf_version > 2
	   && context_die->die_tag != DW_TAG_class_type)
    add_AT_unsigned (die, DW_AT_accessibility, DW_ACCESS_private);
}
