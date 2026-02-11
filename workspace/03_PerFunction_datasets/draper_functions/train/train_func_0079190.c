LANG_LIST(char *path, char *buffer) {
  char lang_str[1024];
  int i = 0;
  int curr_lng = LANG_T(path, -1);

  buffer[0] = '\0';
  do {
    QLANG_T(i);
    strcpybuff(lang_str, "LANGUAGE_NAME");
    htslang_load(lang_str, path);
    if (strlen(lang_str) > 0) {
      if (buffer[0])
        strcatbuff(buffer, "\n");
      strcatbuff(buffer, lang_str);
    }
    i++;
  } while(strlen(lang_str) > 0);
  QLANG_T(curr_lng);
  return i;
}
