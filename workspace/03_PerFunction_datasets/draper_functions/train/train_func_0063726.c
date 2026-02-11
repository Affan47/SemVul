main(int argc, const char **argv)
{
  if (argc != 4)
  {
    fprintf(stderr, "Usage: %s <offset> <stride> <width>\n", argv[0]);
    return EXIT_FAILURE;
  }
  int offset = atoi(argv[1]);
  int stride = atoi(argv[2]);
  int width = atoi(argv[3]);
  if (offset < 0)
  {
    fprintf(stderr, "expected the offset to be nonnegative\n");
    return EXIT_FAILURE;
  }
  if (stride < 1)
  {
    fprintf(stderr, "expected the stride to be positive\n");
    return EXIT_FAILURE;
  }
  if (width < 1)
  {
    fprintf(stderr, "expected the width to be positive\n");
    return EXIT_FAILURE;
  }
  if (width > stride)
  {
    fprintf(stderr, "the width is greater than the stride\n");
    return EXIT_FAILURE;
  }
  if (process(stdin, stdout, offset, stride, width) < 0)
  {
    return EXIT_FAILURE;
  } else {
    return EXIT_SUCCESS;
  }
}
