main (int argc, char **argv)
{
  rtx defn;
  int pattern_lineno, next_insn_code = 0;

  progname = argv[0];
  if (argc <= 1)
    fatal ("no input file name");
  if (init_md_reader_args_cb (argc, argv, parse_option) != SUCCESS_EXIT_CODE)
    return FATAL_EXIT_CODE;

  while ((defn = read_md_rtx (&pattern_lineno, &next_insn_code)) != 0)
    switch (GET_CODE (defn))
      {
      case DEFINE_PREDICATE:
      case DEFINE_SPECIAL_PREDICATE:
	process_define_predicate (defn, pattern_lineno);
	break;

      case DEFINE_CONSTRAINT:
      case DEFINE_MEMORY_CONSTRAINT:
      case DEFINE_ADDRESS_CONSTRAINT:
	process_define_constraint (defn, pattern_lineno);
	break;

      case DEFINE_REGISTER_CONSTRAINT:
	process_define_register_constraint (defn, pattern_lineno);
	break;

      default:
	break;
      }

  if (gen_header)
    write_tm_preds_h ();
  else if (gen_constrs)
    write_tm_constrs_h ();
  else
    write_insn_preds_c ();

  if (have_error || ferror (stdout) || fflush (stdout) || fclose (stdout))
    return FATAL_EXIT_CODE;

  return SUCCESS_EXIT_CODE;
}
