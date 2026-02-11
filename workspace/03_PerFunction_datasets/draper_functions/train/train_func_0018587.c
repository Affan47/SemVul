SuggestPprofCommand(const char* pprof_file_arg) {


  string extra_help;


  const string remote_header =
      "This program is being executed remotely and therefore the pprof\n"
      "command printed above will not work.  Either run this program\n"
      "locally, or adjust the pprof command as follows to allow it to\n"
      "work on your local machine:\n";


  string fetch_cmd;

  RAW_LOG(WARNING,
          "\n\n"
          "If the preceding stack traces are not enough to find "
          "the leaks, try running THIS shell command:\n\n"
          "%s%s %s \"%s\" --inuse_objects --lines --heapcheck "
          " --edgefraction=1e-10 --nodefraction=1e-10 --gv\n"
          "\n"
          "%s"
          "If you are still puzzled about why the leaks are "
          "there, try rerunning this program with "
          "HEAP_CHECK_TEST_POINTER_ALIGNMENT=1 and/or with "
          "HEAP_CHECK_MAX_POINTER_OFFSET=-1\n"
          "If the leak report occurs in a small fraction of runs, "
          "try running with TCMALLOC_MAX_FREE_QUEUE_SIZE of few hundred MB "
          "or with TCMALLOC_RECLAIM_MEMORY=false, "
          "it might help find leaks more repeatably\n",
          fetch_cmd.c_str(),
          "pprof",
          invocation_path().c_str(),
          pprof_file_arg,
          extra_help.c_str()
          );
}
