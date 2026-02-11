read_catalog_stream (FILE *fp, const char *real_filename,
                     const char *logical_filename,
                     catalog_input_format_ty input_syntax)
{
  default_catalog_reader_ty *pop;
  msgdomain_list_ty *mdlp;

  pop = default_catalog_reader_alloc (&default_methods);
  pop->handle_comments = true;
  pop->handle_filepos_comments = (line_comment != 0);
  pop->allow_domain_directives = true;
  pop->allow_duplicates = allow_duplicates;
  pop->allow_duplicates_if_same_msgstr = false;
  pop->file_name = real_filename;
  pop->mdlp = msgdomain_list_alloc (!pop->allow_duplicates);
  pop->mlp = msgdomain_list_sublist (pop->mdlp, pop->domain, true);
  if (input_syntax->produces_utf8)

    pop->mdlp->encoding = po_charset_utf8;
  po_lex_pass_obsolete_entries (true);
  catalog_reader_parse ((abstract_catalog_reader_ty *) pop, fp, real_filename,
                        logical_filename, input_syntax);
  mdlp = pop->mdlp;
  catalog_reader_free ((abstract_catalog_reader_ty *) pop);
  return mdlp;
}
