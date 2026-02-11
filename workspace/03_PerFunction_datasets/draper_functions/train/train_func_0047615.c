utest_compare_line(char *p, esl_pos_t n, int nline_expected)
{
  const char msg[] = "line input fails to match expected";
  int32_t    which = 0;
  int        nc;

  if (esl_memspn(p, n, " \t\r\n") == n) return;

  if (n && *p == ' ') { p++; n--; }
  if (n && *p == '[') { p++; n--; }                else esl_fatal(msg);

  if (! isdigit(*p))                                    esl_fatal(msg);
  if (esl_mem_strtoi32(p, n, 10, &nc, &which) != eslOK) esl_fatal(msg);
  if (which != nline_expected)                          esl_fatal(msg);
  p += nc; n -= nc;

  while (n && isspace(*p)) { p++; n--; }        if (!n) esl_fatal(msg);
  if (! isdigit(*p))                                    esl_fatal(msg);
  if (esl_mem_strtoi32(p, n, 10, &nc, &which) != eslOK) esl_fatal(msg);
  if (which != nline_expected)                          esl_fatal(msg);
  p += nc; n -= nc;

  if (n && *p == ']') { p++; n--; } else esl_fatal(msg);
  if (n && *p == ' ') { p++; n--; }
  if (n != 0) esl_fatal(msg);
}
