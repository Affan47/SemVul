Test_NO_AUTO_CAPTURE() {
  RE_Options options;
  const char *str = "HELLO world";
  string captured;

  printf("Testing Option <no NO_AUTO_CAPTURE>\n");
  if (VERBOSE_TEST)
    printf("parentheses capture text\n");
  RE re("(world|universe)$", options);
  CHECK(re.Extract("\\1", str , &captured));
  CHECK_EQ(captured, "world");
  options.set_no_auto_capture(true);
  printf("testing Option <NO_AUTO_CAPTURE>\n");
  if (VERBOSE_TEST)
    printf("parentheses do not capture text\n");
  re.Extract("\\1",str, &captured );
  CHECK_EQ(captured, "world");
}
