srunner_iterate_tcase_tfuns (SRunner *sr, TCase *tc)
{
  List *tfl;
  TF *tfun;
  TestResult *tr = NULL;

  tfl = tc->tflst;

  for (check_list_front(tfl); !check_list_at_end (tfl); check_list_advance (tfl)) {
    int i;
    tfun = check_list_val (tfl);

    for (i = tfun->loop_start; i < tfun->loop_end; i++)
    {
      log_test_start (sr, tc, tfun);
      switch (srunner_fork_status(sr)) {
      case CK_FORK:
#ifdef _POSIX_VERSION
        tr = tcase_run_tfun_fork (sr, tc, tfun, i);
#else
        eprintf("This version does not support fork", __FILE__, __LINE__);
#endif
        break;
      case CK_NOFORK:
        tr = tcase_run_tfun_nofork (sr, tc, tfun, i);
        break;
      default:
        eprintf("Bad fork status in SRunner", __FILE__, __LINE__);
      }

      if ( NULL != tr ) {
        srunner_add_failure (sr, tr);
        log_test_end(sr, tr);
      }
    }
  }
}
