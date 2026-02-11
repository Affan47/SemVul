test_util_split_lines(void *ptr)
{


  struct split_lines_test_t tests[] = {
    {"", 0, {NULL}},
    {"foo", 3, {"foo", NULL}},
    {"\n\rfoo\n\rbar\r\n", 12, {"foo", "bar", NULL}},
    {"fo o\r\nb\tar", 10, {"fo o", "b.ar", NULL}},
    {"\x0f""f\0o\0\n\x01""b\0r\0\r", 12, {".f.o.", ".b.r.", NULL}},
    {NULL, 0, { NULL }}
  };

  int i, j;
  char *orig_line=NULL;
  smartlist_t *sl=NULL;

  (void)ptr;

  for (i=0; tests[i].orig_line; i++) {
    sl = smartlist_new();

    orig_line = tor_memdup(tests[i].orig_line, tests[i].orig_length + 1);
    tor_split_lines(sl, orig_line, tests[i].orig_length);

    j = 0;
    log_info(LD_GENERAL, "Splitting test %d of length %d",
             i, tests[i].orig_length);
    SMARTLIST_FOREACH(sl, const char *, line,
    {

      tt_int_op(j, <, MAX_SPLIT_LINE_COUNT);

      tt_assert(tests[i].split_line[j] != NULL);
      log_info(LD_GENERAL, "Line %d of test %d, should be <%s>",
               j, i, tests[i].split_line[j]);

      tt_str_op(tests[i].split_line[j], ==, line);
      j++;
    });

    tt_assert(tests[i].split_line[j] == NULL);
    tor_free(orig_line);
    smartlist_free(sl);
    sl = NULL;
  }

 done:
  tor_free(orig_line);
  smartlist_free(sl);
}
