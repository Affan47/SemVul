usage(void) {

  static int first;

  if (!first) {

    fprintf(stderr, "Usage: flow-report [-h]\n");
    fprintf(stderr, "       [-d debug_level] [-s stat_fname] [-S stat_definition]\n");
    fprintf(stderr, "       [-v var=val]\n");
    fprintf(stderr, "\n%s version %s: built by %s\n", PACKAGE, VERSION, FT_PROG_BUILD);

    ++first;

  } else {

    fprintf(stderr, "\nAvailable reports:\n\n");
    ftstat_list_reports(stderr);

  }
}
