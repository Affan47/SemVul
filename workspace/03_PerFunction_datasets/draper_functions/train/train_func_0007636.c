catalog_reader_parse (abstract_catalog_reader_ty *pop, FILE *fp,
                      const char *real_filename, const char *logical_filename,
                      catalog_input_format_ty input_syntax)
{

  parse_start (pop);
  input_syntax->parse (pop, fp, real_filename, logical_filename);
  parse_end (pop);

  if (error_message_count > 0)
    po_xerror (PO_SEVERITY_FATAL_ERROR, NULL,
                NULL, (size_t)(-1), (size_t)(-1), false,
               xasprintf (ngettext ("found %d fatal error",
                                    "found %d fatal errors",
                                    error_message_count),
                          error_message_count));
  error_message_count = 0;
}
