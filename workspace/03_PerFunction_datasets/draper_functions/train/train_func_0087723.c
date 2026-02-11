au_run_test_fork(autounit_test_t *t,
		 autounit_stress_report_t *status)
{


  au_log_start("au_run_test");

  if (t->do_fork) {
    int fork_result;
    int C2P_pipe[2];
    if (pipe(C2P_pipe) < 0) {
      au_assert(t, 0, _("pipe failed"));
      return;
    }

    switch(fork_result = fork()) {
    case -1:
      au_assert(t, 0, _("fork failed"));
      return;

    case 0:
      {

	GString *child_test_result;
	au_run_test_child(t);
	child_test_result = au_test_serialize(t);
	close(C2P_pipe[0]);
	write(C2P_pipe[1],child_test_result->str,child_test_result->len);
	close(C2P_pipe[1]);
	au_log_end("au_run_test");
	exit(0);
      }

    default:
      {

	gint childstatus;
	close(C2P_pipe[1]);
	waitpid(fork_result, &childstatus, 0);

	if (WIFEXITED(childstatus)) {
	  autounit_test_t *tmp_t;
	  GString *parent_test_result = au_read_netstring(C2P_pipe[0]);
	  tmp_t = au_test_unserialize(parent_test_result);


	  t->failed_assertions += tmp_t->failed_assertions;
	  t->test_seconds_elapsed = tmp_t->test_seconds_elapsed;
	  t->test_useconds_elapsed = tmp_t->test_useconds_elapsed;
	  t->test_status = g_string_append(t->test_status,
                                           tmp_t->test_status->str);
          au_delete_test(tmp_t);
	} else {
	  if (WIFSIGNALED(childstatus)) {
	    au_assert(t, 0, _("test failed with signal"));
	  }
#ifdef WCOREDUMP
	  if (WCOREDUMP(childstatus)) {
            t->failed_assertions++;
	    au_assert(t, 0, _("test failed with core dump"));
	  }
#endif
	}
      }
    }
  }
  else {
    au_run_test_child(t);
  }

  if (t->failed_assertions > 0) {
    g_print(_("!"));
  } else {
    if ((*(status->round) % status->modulo) == 0) {
      g_print(_("."));
    }
  }
}
