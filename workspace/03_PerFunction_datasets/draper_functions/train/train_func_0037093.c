main(int argc, char **argv)
{
  char  tmpfile[32] = "esltmpXXXXXX";
  FILE *fp;

  char stream[] = "# Full line comment\n"
                  "token1  # Trailing comment\n"
                  "\n"
                  "   \n"
                  "   # sowing comment/whitespace confusion...\n"
                  "token2\ttoken3  token4\n"
                  "token5";


  if (esl_tmpfile_named(tmpfile, &fp) != eslOK) esl_fatal("File open failed");
  fprintf(fp, "%s", stream);
  fclose(fp);


  utest_GetToken(tmpfile);
  utest_GetTokenOnLine(tmpfile);
  utest_GetTokenBuffered(stream);

  remove(tmpfile);
  return 0;
}
