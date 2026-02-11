tac_nonseekable (int input_fd, const char *file)
{
  FILE *tmp_stream;
  char *tmp_file;
  if (!copy_to_temp (&tmp_stream, &tmp_file, input_fd, file))
    return false;

  bool ok = tac_seekable (fileno (tmp_stream), tmp_file);
  return ok;
}
