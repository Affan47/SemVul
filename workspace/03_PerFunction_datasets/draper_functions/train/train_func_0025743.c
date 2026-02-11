parseNameToUnicode(GooString *name) {
  char *tok1, *tok2;
  FILE *f;
  char buf[256];
  int line;
  Unicode u;

  if (!(f = fopen(name->getCString(), "r"))) {
    error(-1, "Couldn't open 'nameToUnicode' file '%s'",
	  name->getCString());
    return;
  }
  line = 1;
  while (getLine(buf, sizeof(buf), f)) {
    tok1 = strtok(buf, " \t\r\n");
    tok2 = strtok(NULL, " \t\r\n");
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
