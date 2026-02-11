main (int argc, char **argv)
{
  newline_t newline = ASCII_CR;

  if (argc < 3)
  {
    print_help ();
    return -1;
  }

  if (argc == 4 && !strcmp (argv[3], "--unix"))
    newline = ASCII_LF;

  return run_conv (argv[1], argv[2], newline);
}
