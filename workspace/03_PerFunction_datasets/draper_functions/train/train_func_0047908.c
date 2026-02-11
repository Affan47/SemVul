mangle_decl_string (const tree decl)
{
  const char *result;

  start_mangling (decl);

  if (TREE_CODE (decl) == TYPE_DECL)
    write_type (TREE_TYPE (decl));
  else
    write_mangled_name (decl, true);

  result = finish_mangling (true);
  if (DEBUG_MANGLE)
    fprintf (stderr, "mangle_decl_string = '%s'\n\n", result);
  return result;
}
