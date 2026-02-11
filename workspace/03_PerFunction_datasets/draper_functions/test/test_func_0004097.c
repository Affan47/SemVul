main(int argc, const char **argv)
{
  if (argc != 2)
  {
    fprintf(stderr, "Usage: %s <ndoubles-per-box>\n", argv[0]);
    return EXIT_FAILURE;
  }
  int ndoubles_per_box = atoi(argv[1]);
  if (ndoubles_per_box < 1)
  {
    fprintf(stderr, "expected at least one double per box\n");
    return EXIT_FAILURE;
  }
  if (process(stdin, stdout, ndoubles_per_box) < 0)
  {
    return EXIT_FAILURE;
  } else {
    return EXIT_SUCCESS;
  }
}
