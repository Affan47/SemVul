preprocess_file (cpp_reader *pfile)
{


  if (flag_no_output)
    {

      while (pfile->buffer->prev)
	cpp_scan_nooutput (pfile);
      cpp_scan_nooutput (pfile);
    }
  else if (cpp_get_options (pfile)->traditional)
    scan_translation_unit_trad (pfile);
  else if (cpp_get_options (pfile)->directives_only
	   && !cpp_get_options (pfile)->preprocessed)
    scan_translation_unit_directives_only (pfile);
  else
    scan_translation_unit (pfile);


  if (flag_dump_macros == 'M')
    cpp_forall_identifiers (pfile, dump_macro, NULL);


  if (print.printed)
    putc ('\n', print.outf);
}
