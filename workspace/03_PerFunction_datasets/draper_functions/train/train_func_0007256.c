verify_numeric (const char *s, const char *end)
{
  if (errno)
    {
      error (0, errno, "%s", s);
      exit_status = EXIT_FAILURE;
    }
  else if (*end)
    {
      if (s == end)
        error (0, 0, _("%s: expected a numeric value"), s);
      else
        error (0, 0, _("%s: value not completely converted"), s);
      exit_status = EXIT_FAILURE;
    }
}
