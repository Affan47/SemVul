manual_input (int prompt)
{
  int cont = 1;
  while (cont) {
    char buffer[BUF_SIZE];
    int i = 0;
    lua_beginblock();
    if (prompt)
      printf("%s", lua_getstring(lua_getglobal("_PROMPT")));
    for(;;) {
      int c = getchar();
      if (c == EOF) {
        cont = 0;
        break;
      }
      else if (c == '\n') {
        if (i>0 && buffer[i-1] == '\\')
          buffer[i-1] = '\n';
        else break;
      }
      else if (i >= BUF_SIZE-1) {
        fprintf(stderr, "lua: argument line too long\n");
        break;
      }
      else buffer[i++] = c;
    }
    buffer[i] = 0;
    ldo(lua_dostring, buffer);
    lua_endblock();
  }
  printf("\n");
}
