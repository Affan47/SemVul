check_text(uch *buffer, int maxsize)
{
  int j;

  for (j = 0; j < maxsize; ++j) {
    if (buffer[j] == 0) {
      cli_dbgmsg("PNG: text contains NULL character(s)\n");
      return 1;
    } else if (latin1_text_discouraged[buffer[j]]) {
      cli_dbgmsg("PNG: text has control character(s)\n");
      return 1;
    }
  }
  return 0;
}
