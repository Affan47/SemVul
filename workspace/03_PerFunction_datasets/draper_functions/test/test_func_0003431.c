c_parse_file (void)
{
  static bool already_called = false;

  if (already_called)
    {
      sorry ("inter-module optimizations not implemented for C++");
      return;
    }
  already_called = true;

  the_parser = cp_parser_new ();
  push_deferring_access_checks (flag_access_control
				? dk_no_deferred : dk_no_check);
  cp_parser_translation_unit (the_parser);
  the_parser = NULL;
}
