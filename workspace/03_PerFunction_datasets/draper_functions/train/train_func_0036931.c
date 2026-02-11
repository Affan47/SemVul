gtp_analyze_eyegraph(char *s)
{
  struct eyevalue value;
  char analyzed_eyegraph[1024];
  int result = analyze_eyegraph(s, &value, analyzed_eyegraph);

  if (result == 0)
    return gtp_failure("failed to analyze");

  return gtp_success("%s\n%s", eyevalue_to_string(&value), analyzed_eyegraph);
}
