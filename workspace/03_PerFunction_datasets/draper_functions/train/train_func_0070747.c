tokenize_args_string (char *args_string, int *argcp, char ***argvp)
{
  static char horizontal_space[] = " \t";
  char **argv_0 = xmalloc (sizeof(char *) * strlen (args_string) / 2);
  char **argv = argv_0;
  char *arg;

  *argv++ = program_name;
  arg = strsep (&args_string, horizontal_space);
  while (arg)
    {
      *argv++ = arg;
      arg = strsep (&args_string, horizontal_space);
    }
  *argcp = argv - argv_0;
  *argvp = xnrealloc (argv_0, *argcp, sizeof **argvp);
}
