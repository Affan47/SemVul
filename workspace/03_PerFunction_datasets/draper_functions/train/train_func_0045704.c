coverage_begin_function (unsigned lineno_checksum, unsigned cfg_checksum)
{
  expanded_location xloc;
  unsigned long offset;


  if (no_coverage || !bbg_file_name)
    return 0;

  xloc = expand_location (DECL_SOURCE_LOCATION (current_function_decl));


  offset = gcov_write_tag (GCOV_TAG_FUNCTION);
  gcov_write_unsigned (current_function_funcdef_no + 1);
  gcov_write_unsigned (lineno_checksum);
  gcov_write_unsigned (cfg_checksum);
  gcov_write_string (IDENTIFIER_POINTER
		     (DECL_ASSEMBLER_NAME (current_function_decl)));
  gcov_write_string (xloc.file);
  gcov_write_unsigned (xloc.line);
  gcov_write_length (offset);

  return !gcov_is_error ();
}
