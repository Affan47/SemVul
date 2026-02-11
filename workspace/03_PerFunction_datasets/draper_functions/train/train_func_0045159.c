parseNameToUnicode(GooString *name) {
  char *tok1, *tok2;
  FILE *f;
  char buf[256];
  int line;
  Unicode u;
  char *tokptr;

  if (!(f = fopen(name->getCString(), "r"))) {
    error(-1, "Couldn't open 'nameToUnicode' file '%s'",
	  name->getCString());
    return;
  }
  line = 1;
  while (getLine(buf, sizeof(buf), f)) {
    tok1 = strtok_r(buf, " \t\r\n", &tokptr);
    tok2 = strtok_r(NULL, " \t\r\n", &tokptr);
    if (tok1 && tok2) {
      sscanf(tok1, "%x", &u);
      nameToUnicode->add(tok2, u);
    } else {
      error(-1, "Bad line in 'nameToUnicode' file (%s:%d)",
	    name->getCString(), line);
    }
    ++line;
  }
  fclose(f);
}
