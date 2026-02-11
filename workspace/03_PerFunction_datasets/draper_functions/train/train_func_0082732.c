main (int argc, char **argv)
{
  rtx desc;
  int pattern_lineno;
  int code;

  progname = "genconditions";

  if (!init_rtx_reader_args (argc, argv))
    return (FATAL_EXIT_CODE);


  while (1)
    {
      desc = read_md_rtx (&pattern_lineno, &code);
      if (desc == NULL)
	break;


      switch (GET_CODE (desc))
	{
	default:
	  break;

	case DEFINE_INSN:
	case DEFINE_EXPAND:
	  add_c_test (XSTR (desc, 2), -1);


	  if (!strcmp (XSTR (desc, 0), "eh_return"))
	    saw_eh_return = 1;
	  break;

	case DEFINE_SPLIT:
	case DEFINE_PEEPHOLE:
	case DEFINE_PEEPHOLE2:
	  add_c_test (XSTR (desc, 1), -1);
	  break;
	}
    }

  write_header ();
  write_conditions ();
  write_writer ();

  fflush (stdout);
  return (ferror (stdout) != 0 ? FATAL_EXIT_CODE : SUCCESS_EXIT_CODE);
}
