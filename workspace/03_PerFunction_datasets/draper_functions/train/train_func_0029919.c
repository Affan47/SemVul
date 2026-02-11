c_parse_file (void)
{


  c_parser tparser;

  memset (&tparser, 0, sizeof tparser);
  the_parser = &tparser;

  if (c_parser_peek_token (&tparser)->pragma_kind == PRAGMA_GCC_PCH_PREPROCESS)
    c_parser_pragma_pch_preprocess (&tparser);

  the_parser = ggc_alloc_c_parser ();
  *the_parser = tparser;


  if (flag_exceptions)
    using_eh_for_cleanups ();

  c_parser_translation_unit (the_parser);
  the_parser = NULL;
}
