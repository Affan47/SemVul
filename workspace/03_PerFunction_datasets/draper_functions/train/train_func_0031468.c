lower_bound_default (void)
{
  switch (get_AT_unsigned (comp_unit_die (), DW_AT_language))
    {
    case DW_LANG_C:
    case DW_LANG_C89:
    case DW_LANG_C99:
    case DW_LANG_C_plus_plus:
    case DW_LANG_ObjC:
    case DW_LANG_ObjC_plus_plus:
    case DW_LANG_Java:
      return 0;
    case DW_LANG_Fortran77:
    case DW_LANG_Fortran90:
    case DW_LANG_Fortran95:
      return 1;
    case DW_LANG_UPC:
    case DW_LANG_D:
    case DW_LANG_Python:
      return dwarf_version >= 4 ? 0 : -1;
    case DW_LANG_Ada95:
    case DW_LANG_Ada83:
    case DW_LANG_Cobol74:
    case DW_LANG_Cobol85:
    case DW_LANG_Pascal83:
    case DW_LANG_Modula2:
    case DW_LANG_PLI:
      return dwarf_version >= 4 ? 1 : -1;
    default:
      return -1;
    }
}
