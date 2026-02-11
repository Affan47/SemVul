find_torrc_filename(int argc, char **argv,
                    int defaults_file,
                    int *using_default_torrc, int *ignore_missing_torrc)
{
  char *fname=NULL;
  int i;
  const char *fname_opt = defaults_file ? "--defaults-torrc" : "-f";
  const char *ignore_opt = defaults_file ? NULL : "--ignore-missing-torrc";

  if (defaults_file)
    *ignore_missing_torrc = 1;

  for (i = 1; i < argc; ++i) {
    if (i < argc-1 && !strcmp(argv[i],fname_opt)) {
      if (fname) {
        log(LOG_WARN, LD_CONFIG, "Duplicate %s options on command line.",
            fname_opt);
        tor_free(fname);
      }
      fname = expand_filename(argv[i+1]);

      {
        char *absfname;
        absfname = make_path_absolute(fname);
        tor_free(fname);
        fname = absfname;
      }

      *using_default_torrc = 0;
      ++i;
    } else if (ignore_opt && !strcmp(argv[i],ignore_opt)) {
      *ignore_missing_torrc = 1;
    }
  }

  if (*using_default_torrc) {

    const char *dflt = get_default_conf_file(defaults_file);
    if (dflt && file_status(dflt) == FN_FILE) {
      fname = tor_strdup(dflt);
    } else {
#ifndef _WIN32
      char *fn = NULL;
      if (!defaults_file)
        fn = expand_filename("~/.torrc");
      if (fn && file_status(fn) == FN_FILE) {
        fname = fn;
      } else {
        tor_free(fn);
        fname = tor_strdup(dflt);
      }
#else
      fname = tor_strdup(dflt);
#endif
    }
  }
  return fname;
}
