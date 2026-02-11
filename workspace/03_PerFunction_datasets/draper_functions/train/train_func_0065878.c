srunner_iterate_suites (SRunner *sr,
				    enum print_output print_mode)

{
  List *slst;
  List *tcl;
  TCase *tc;

  slst = sr->slst;

  for (list_front(slst); !list_at_end(slst); list_advance(slst)) {
    Suite *s = list_val(slst);

    log_suite_start (sr, s);

    tcl = s->tclst;

    for (list_front(tcl);!list_at_end (tcl); list_advance (tcl)) {
      tc = list_val (tcl);
      srunner_run_tcase (sr, tc);
    }

    log_suite_end (sr, s);
  }
}
