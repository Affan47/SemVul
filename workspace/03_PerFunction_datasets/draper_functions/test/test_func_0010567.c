utest_memtok(void)
{
  char      msg[]       = "esl_memtok() unit test failed";
  char     *teststring;
  esl_pos_t n;
  char     *s;
  char     *tok;
  esl_pos_t toklen;

  if (esl_strdup("This is\t a sentence.", -1, &teststring) != eslOK) esl_fatal(msg);

  s = teststring;
  n = strlen(teststring);
  if (esl_memtok(&s, &n, " ", &tok, &toklen) != eslOK)     esl_fatal(msg);
  if (toklen != 4)                                         esl_fatal(msg);
  if (memcmp(tok, "This", toklen) != 0)                    esl_fatal(msg);
  if (*s != 'i')                                           esl_fatal(msg);

  if (esl_memtok(&s, &n, " \t", &tok, &toklen) != eslOK)   esl_fatal(msg);
  if (toklen != 2)                                         esl_fatal(msg);
  if (memcmp(tok, "is", toklen) != 0)                      esl_fatal(msg);
  if (*s != 'a')                                           esl_fatal(msg);

  if (esl_memtok(&s, &n, "\n", &tok, &toklen)  != eslOK)   esl_fatal(msg);
  if (toklen != 11)                                        esl_fatal(msg);
  if (memcmp(tok, "a sentence.", toklen) != 0)             esl_fatal(msg);
  if (*s != '\0')                                          esl_fatal(msg);
  if (n  != 0)                                             esl_fatal(msg);

  if (esl_memtok(&s, &n, "\n", &tok, &toklen)  != eslEOL)  esl_fatal(msg);
  if (toklen != 0)                                         esl_fatal(msg);
  if (tok    != NULL)                                      esl_fatal(msg);

  free(teststring);
  return;
}
