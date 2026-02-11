add_accessibility_attribute (dw_die_ref die, tree decl)
{


  if (TREE_PROTECTED (decl))
    add_AT_unsigned (die, DW_AT_accessibility, DW_ACCESS_protected);
  else if (TREE_PRIVATE (decl))
    {
      if (dwarf_version == 2
	  || die->die_parent == NULL
	  || die->die_parent->die_tag != DW_TAG_class_type)
	add_AT_unsigned (die, DW_AT_accessibility, DW_ACCESS_private);
    }
  else if (dwarf_version > 2
	   && die->die_parent
	   && die->die_parent->die_tag == DW_TAG_class_type)
    add_AT_unsigned (die, DW_AT_accessibility, DW_ACCESS_public);
}
