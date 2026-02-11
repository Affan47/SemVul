Swig_warnfilter(const_String_or_char_ptr wlist, int add) {
  char *c;
  char *cw;
  String *s;
  if (!filter)
    filter = NewStringEmpty();

  s = NewString("");
  Clear(s);
  cw = Char(wlist);
  while (*cw != '\0') {
    if (*cw != ' ') {
      Putc(*cw, s);
    }
    ++cw;
  }
  c = Char(s);
  c = strtok(c, ", ");
  while (c) {
    if (isdigit((int) *c) || (*c == '+') || (*c == '-')) {


      if (add) {
	Insert(filter, 0, c);
	if (isdigit((int) *c)) {
	  Insert(filter, 0, "-");
	}
      } else {
	char *temp = (char *)malloc(sizeof(char)*strlen(c) + 2);
	if (isdigit((int) *c)) {
	  sprintf(temp, "-%s", c);
	} else {
	  strcpy(temp, c);
	}
	Replace(filter, temp, "", DOH_REPLACE_FIRST);
        free(temp);
      }
    }
    c = strtok(NULL, ", ");
  }
  Delete(s);
}
