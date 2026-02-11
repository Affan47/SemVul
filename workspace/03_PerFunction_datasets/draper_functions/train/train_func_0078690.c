fh_error (format_data_t form, int argc, char *argv[])
{
  int i;
  FILE *s = ostream;
  int *c = column;

  ostream = stderr;
  column = &column_stderr;
  for (i = 0; i < argc; i++)
    select_arg (form, argc, argv, i);
  ostream = s;
  column = c;
}
