record_builtin_type (const char *name, tree type, bool artificial_p)
{
  tree type_decl = build_decl (input_location,
			       TYPE_DECL, get_identifier (name), type);
  DECL_ARTIFICIAL (type_decl) = artificial_p;
  TYPE_ARTIFICIAL (type) = artificial_p;
  gnat_pushdecl (type_decl, Empty);

  if (debug_hooks->type_decl)
    debug_hooks->type_decl (type_decl, false);
}
