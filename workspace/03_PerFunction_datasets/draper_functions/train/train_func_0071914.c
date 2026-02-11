check_args (int argc, char *argv[])
{
  int i;

  for (i = 1; i < argc && argv[i][0] == '-'; i++)
  {
    check_arg (&i, argc, argv[i], (((i+1) < argc) ? argv[i+1] : ""));
  }

  if (flags.no_config == FALSE)
  {
    if (!read_config(getenv("ID3REN"), ""))
      if (!read_config(getenv("HOME"), CONFIG_HOME))
  #ifdef __WIN32__
        read_config(program_path, CONFIG_GLOBAL);
  #else
        read_config("/etc", CONFIG_GLOBAL);
  #endif
  }

  return i;
}
