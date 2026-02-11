string_to_integer (bool count_lines, const char *n_string)
{
  strtol_error s_err;
  uintmax_t n;

  s_err = xstrtoumax (n_string, NULL, 10, &n, "bkKmMGTPEZY0");

  if (s_err == LONGINT_OVERFLOW)
    {
      error (EXIT_FAILURE, 0,
             _("%s: %s is so large that it is not representable"), n_string,
             count_lines ? _("number of lines") : _("number of bytes"));
    }

  if (s_err != LONGINT_OK)
    {
      error (EXIT_FAILURE, 0, "%s: %s", n_string,
             (count_lines
              ? _("invalid number of lines")
              : _("invalid number of bytes")));
    }

  return n;
}
