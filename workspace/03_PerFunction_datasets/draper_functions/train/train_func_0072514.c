string_version_compare (void) {
  int ret;
  STACK_0 = check_string(STACK_0);
  STACK_1 = check_string(STACK_1);
  with_string_0(STACK_0,GLO(misc_encoding),s1, {
      with_string_0(STACK_1,GLO(misc_encoding),s2, {
          begin_system_call(); ret = strverscmp(s2,s1); end_system_call();
        });
    });
  skipSTACK(2);
  return ret;
}
