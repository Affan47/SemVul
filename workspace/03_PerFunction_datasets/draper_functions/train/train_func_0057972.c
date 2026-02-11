mangle_special_for_type (const tree type, const char *code)
{
  const char *result;


  start_mangling (type);


  write_string ("_Z");
  write_string (code);


  write_type (type);
  result = finish_mangling (false);

  if (DEBUG_MANGLE)
    fprintf (stderr, "mangle_special_for_type = %s\n\n", result);

  return get_identifier (result);
}
