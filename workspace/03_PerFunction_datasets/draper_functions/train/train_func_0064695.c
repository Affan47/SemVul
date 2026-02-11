file_args(const char *path, argv_t *grid,
			  argv_t **queue_list, int *queue_head_p,
			  int *queue_tail_p, int *okay_bp)
{
  char	**argv, **argv_p;
  int	arg_c, max;
  FILE	*infile;
  char	line[FILE_LINE_SIZE], *line_p;


  if (strcmp(path, "-") == 0) {
    infile = stdin;
  }
  else {
    infile = fopen(path, "r");
  }
  if (infile == NULL) {
    *okay_bp = ARGV_FALSE;
    if (argv_error_stream != NULL) {
      (void)fprintf(argv_error_stream,
		    "%s: could not load command-line arguments from: %s\n",
		    argv_program, path);
    }
    if (argv_interactive) {
      (void)exit(argv_error_code);
    }
    return;
  }


  arg_c = 0;
  max = ARRAY_INCR;
  argv = malloc(sizeof(char *) * max);
  if (argv == NULL) {
    *okay_bp = ARGV_FALSE;
    if (infile != stdin) {
      (void)fclose(infile);
    }
    if (argv_error_stream != NULL) {
      (void)fprintf(argv_error_stream,
		    "%s: memory error during argument processing\n",
		    argv_program);
    }
    if (argv_interactive) {
      (void)exit(argv_error_code);
    }
    return;
  }
  argv_p = argv;


  while (fgets(line, sizeof(line), infile) != NULL) {

    for (line_p = line; *line_p != '\n' && *line_p != '\0'; line_p++) {
    }
    *line_p = '\0';


    if (line_p == line) {
      continue;
    }

    *argv_p = string_copy(line);
    if (*argv_p == NULL) {
      *okay_bp = ARGV_FALSE;
      return;
    }

    argv_p++;
    arg_c++;


    if (arg_c == max) {
      max += ARRAY_INCR;
      argv = realloc(argv, sizeof(char *) * max);
      if (argv == NULL) {
	*okay_bp = ARGV_FALSE;
	if (infile != stdin) {
	  (void)fclose(infile);
	}
	if (argv_error_stream != NULL) {
	  (void)fprintf(argv_error_stream,
			"%s: memory error during argument processing\n",
			argv_program);
	}
	if (argv_interactive) {
	  (void)exit(argv_error_code);
	}
	return;
      }
      argv_p = argv + arg_c;
    }
  }


  do_list(grid, arg_c, argv, queue_list, queue_head_p, queue_tail_p, okay_bp);


  for (argv_p = argv; argv_p < argv + arg_c; argv_p++) {
    free(*argv_p);
  }
  free(argv);

  if (infile != stdin) {
    (void)fclose(infile);
  }
}
