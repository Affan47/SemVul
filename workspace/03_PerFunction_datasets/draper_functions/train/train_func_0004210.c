diagnostic_action_after_output (diagnostic_context *context,
				diagnostic_info *diagnostic)
{
  switch (diagnostic->kind)
    {
    case DK_DEBUG:
    case DK_NOTE:
    case DK_ANACHRONISM:
    case DK_WARNING:
      break;

    case DK_ERROR:
    case DK_SORRY:
      if (context->abort_on_error)
	real_abort ();
      if (context->fatal_errors)
	{
	  fnotice (stderr, "compilation terminated due to -Wfatal-errors.\n");
	  diagnostic_finish (context);
	  exit (FATAL_EXIT_CODE);
	}
      if (context->max_errors != 0
	  && ((unsigned) (diagnostic_kind_count (context, DK_ERROR)
			  + diagnostic_kind_count (context, DK_SORRY))
	      >= context->max_errors))
	{
	  fnotice (stderr,
		   "compilation terminated due to -fmax-errors=%u.\n",
		   context->max_errors);
	  diagnostic_finish (context);
	  exit (FATAL_EXIT_CODE);
	}
      break;

    case DK_ICE:
      {
	struct backtrace_state *state =
	  backtrace_create_state (NULL, 0, bt_err_callback, NULL);
	int count = 0;
	if (state != NULL)
	  backtrace_full (state, 2, bt_callback, bt_err_callback,
			  (void *) &count);

	if (context->abort_on_error)
	  real_abort ();

	fnotice (stderr, "Please submit a full bug report,\n"
		 "with preprocessed source if appropriate.\n");
	if (count > 0)
	  fnotice (stderr,
		   ("Please include the complete backtrace "
		    "with any bug report.\n"));
	fnotice (stderr, "See %s for instructions.\n", bug_report_url);

	exit (ICE_EXIT_CODE);
      }

    case DK_FATAL:
      if (context->abort_on_error)
	real_abort ();
      diagnostic_finish (context);
      fnotice (stderr, "compilation terminated.\n");
      exit (ICE_EXIT_CODE);

    default:
      gcc_unreachable ();
    }
}
