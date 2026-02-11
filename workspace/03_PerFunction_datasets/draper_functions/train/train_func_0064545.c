ParseFlagValue(const char* str,
                           const char* flag,
                           bool def_optional) {

  if (str == NULL || flag == NULL) return NULL;


  const String flag_str = String::Format("--%s%s", GTEST_FLAG_PREFIX_, flag);
  const size_t flag_len = flag_str.length();
  if (strncmp(str, flag_str.c_str(), flag_len) != 0) return NULL;


  const char* flag_end = str + flag_len;


  if (def_optional && (flag_end[0] == '\0')) {
    return flag_end;
  }


  if (flag_end[0] != '=') return NULL;


  return flag_end + 1;
}
