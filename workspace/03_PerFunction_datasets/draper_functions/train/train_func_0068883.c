write_typed_alloc_def (bool variable_size, const char *type_specifier,
		       const char *type_name, const char *allocator_type,
		       enum alloc_quantity quantity, enum alloc_zone zone)
{
  bool two_args = variable_size && (quantity == vector);
  bool third_arg = ((zone == specific_zone)
		    && (variable_size || (quantity == vector)));

  oprintf (header_file, "#define ggc_alloc_%s%s", allocator_type, type_name);
  oprintf (header_file, "(%s%s%s%s%s) ",
	   (variable_size ? "SIZE" : ""),
	   (two_args ? ", " : ""),
	   (quantity == vector) ? "n" : "",
	   (third_arg ? ", " : ""), (zone == specific_zone) ? "z" : "");
  oprintf (header_file, "((%s%s *)", type_specifier, type_name);
  oprintf (header_file, "(ggc_internal_%salloc_stat (", allocator_type);
  if (zone == specific_zone)
    oprintf (header_file, "z, ");
  if (variable_size)
    oprintf (header_file, "SIZE");
  else
    oprintf (header_file, "sizeof (%s%s)", type_specifier, type_name);
  if (quantity == vector)
    oprintf (header_file, ", n");
  oprintf (header_file, " MEM_STAT_INFO)))\n");
}
