add_calling_convention_attribute (dw_die_ref subr_die, tree decl)
{
  enum dwarf_calling_convention value = DW_CC_normal;

  value = ((enum dwarf_calling_convention)
	   targetm.dwarf_calling_convention (TREE_TYPE (decl)));

  if (is_fortran ()
      && !strcmp (IDENTIFIER_POINTER (DECL_ASSEMBLER_NAME (decl)), "MAIN__"))
    {


      value = DW_CC_program;

      if (dwarf_version >= 4 || !dwarf_strict)
	add_AT_flag (subr_die, DW_AT_main_subprogram, 1);
    }


  if (value && (value != DW_CC_normal))
    add_AT_unsigned (subr_die, DW_AT_calling_convention, value);
}
