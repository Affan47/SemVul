cloneargs(int argc, char **argv)
{
  int x;
  char **args;

  args = (char **) malloc(sizeof(char*) * argc);
  if (args == NULL) {
    errormsg("out of memory!\n");
    exit(1);
  }

  for (x = 0; x < argc; x++) {
    args[x] = strdup(argv[x]);
    if (args[x] == NULL) {
      free(args);
      errormsg("out of memory!\n");
      exit(1);
    }
  }

  return args;
}
