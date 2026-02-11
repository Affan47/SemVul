GetOneOptionResult(
                const char *option_name,
                const char *regex,
                const char *str,
                RE_Options options,
                bool full,
                string expected) {

  printf("Testing Option <%s>\n", option_name);
  if(VERBOSE_TEST)
    printf("/%s/ finds \"%s\" within \"%s\" \n",
                    regex,
                    expected.c_str(),
                    str);
  string captured("");
  if (full)
    RE(regex,options).FullMatch(str, &captured);
  else
    RE(regex,options).PartialMatch(str, &captured);
  CHECK_EQ(captured, expected);
}
