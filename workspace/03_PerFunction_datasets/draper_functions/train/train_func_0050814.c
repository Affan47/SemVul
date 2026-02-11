initialize ( int argc, char** argv )
{
  static const char var_not_found[] =
#ifndef __STDC__
    "fixincl ERROR:  %s environment variable not defined\n"
#else
    "fixincl ERROR:  %s environment variable not defined\n"
    "each of these must be defined:\n"
# define _ENV_(vv,mm,nn,tt) "\t" nn "  - " tt "\n"
  ENV_TABLE
# undef _ENV_
#endif
    ;

  xmalloc_set_program_name (argv[0]);

  switch (argc)
    {
    case 1:
      break;

    case 2:
      if (strcmp (argv[1], "-v") == 0)
        do_version ();
      if (freopen (argv[1], "r", stdin) == (FILE*)NULL)
        {
          fprintf (stderr, "Error %d (%s) reopening %s as stdin\n",
                   errno, xstrerror (errno), argv[1] );
          exit (EXIT_FAILURE);
        }
      break;

    default:
      fputs ("fixincl ERROR:  too many command line arguments\n", stderr);
      exit (EXIT_FAILURE);
    }

#ifdef SIGCHLD


  signal (SIGCHLD, SIG_DFL);
#endif

#define _ENV_(v,m,n,t)   { tSCC var[] = n;  \
  v = getenv (var); if (m && (v == NULL)) { \
  fprintf (stderr, var_not_found, var);     \
  exit (EXIT_FAILURE); } }

ENV_TABLE

#undef _ENV_

  if (ISDIGIT ( *pz_verbose ))
    verbose_level = (te_verbose)atoi( pz_verbose );
  else
    switch (*pz_verbose) {
    case 's':
    case 'S':
      verbose_level = VERB_SILENT;     break;

    case 'f':
    case 'F':
      verbose_level = VERB_FIXES;      break;

    case 'a':
    case 'A':
      verbose_level = VERB_APPLIES;    break;

    default:
    case 'p':
    case 'P':
      verbose_level = VERB_PROGRESS;   break;

    case 't':
    case 'T':
      verbose_level = VERB_TESTS;      break;

    case 'e':
    case 'E':
      verbose_level = VERB_EVERYTHING; break;
    }
  if (verbose_level >= VERB_EVERYTHING) {
    verbose_level = VERB_EVERYTHING;
    fputs ("fixinc verbosity:  EVERYTHING\n", stderr);
  }
  while ((pz_find_base[0] == '.') && (pz_find_base[1] == '/'))
    pz_find_base += 2;
  if ((pz_find_base[0] != '.') || (pz_find_base[1] != NUL))
    find_base_len = strlen( pz_find_base );


  run_compiles ();

# ifdef SEPARATE_FIX_PROC


  pz_temp_file = tempnam( NULL, "fxinc" );
# endif

  signal (SIGQUIT, SIG_IGN);
#ifdef SIGIOT
  signal (SIGIOT,  SIG_IGN);
#endif
#ifdef SIGPIPE
  signal (SIGPIPE, SIG_IGN);
#endif
  signal (SIGALRM, SIG_IGN);
  signal (SIGTERM, SIG_IGN);
}
