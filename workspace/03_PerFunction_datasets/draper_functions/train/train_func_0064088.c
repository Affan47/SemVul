include_spec_function (int argc, const char **argv)
{
  char *file;

  if (argc != 1)
    abort ();

  file = find_a_file (&startfile_prefixes, argv[0], R_OK, true);
  read_specs (file ? file : argv[0], false, false);

  return NULL;
}
