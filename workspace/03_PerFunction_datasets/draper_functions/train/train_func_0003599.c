except_archive(int argc, int optind, char *argv[],
                           struct opts_val *val)
{
  if(val->use_file) {
    if(argc - optind != 1)
      errx(EXIT_FAILURE, "except archive name");
    val->file = argv[optind];
  }
  else if(argc - optind)
    errx(EXIT_FAILURE, "except no arguments");
  else
    val->file = NULL;
}
