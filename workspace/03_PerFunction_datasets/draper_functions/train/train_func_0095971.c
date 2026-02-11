test_test (p_test, pz_test_file)
     tTestDesc *p_test;
     char*      pz_test_file;
{
  tSCC cmd_fmt[] =
"file=%s\n\
if ( test %s ) > /dev/null 2>&1\n\
then echo TRUE\n\
else echo FALSE\n\
fi";

  char *pz_res;
  int res;

  static char cmd_buf[4096];

  sprintf (cmd_buf, cmd_fmt, pz_test_file, p_test->pz_test_text);
  pz_res = run_shell (cmd_buf);

  switch (*pz_res) {
  case 'T':
    res = APPLY_FIX;
    break;

  case 'F':
    res = SKIP_FIX;
    break;

  default:
    fprintf (stderr, "Script yielded bogus result of `%s':\n%s\n\n",
             pz_res, cmd_buf );
  }

  free ((void *) pz_res);
  return res;
}
