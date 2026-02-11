add_src_coords_attributes (dw_die_ref die, tree decl)
{
  expanded_location s;

  if (DECL_SOURCE_LOCATION (decl) == UNKNOWN_LOCATION)
    return;
  s = expand_location (DECL_SOURCE_LOCATION (decl));
  add_AT_file (die, DW_AT_decl_file, lookup_filename (s.file));
  add_AT_unsigned (die, DW_AT_decl_line, s.line);
}
