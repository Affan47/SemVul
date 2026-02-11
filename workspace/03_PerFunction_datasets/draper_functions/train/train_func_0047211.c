DohNewString(const DOH *so) {
  int l = 0, max;
  String *str;
  char *s;
  int hashkey = -1;
  if (DohCheck(so)) {
    str = (String *) ObjData(so);
    s = (char *) String_data((String *) so);
    l = s ? str->len : 0;
    hashkey = str->hashkey;
  } else {
    s = (char *) so;
    l = s ? (int) strlen(s) : 0;
  }

  str = (String *) DohMalloc(sizeof(String));
  str->hashkey = hashkey;
  str->sp = 0;
  str->line = 1;
  str->file = 0;
  max = INIT_MAXSIZE;
  if (s) {
    if ((l + 1) > max)
      max = l + 1;
  }
  str->str = (char *) DohMalloc(max);
  str->maxsize = max;
  if (s) {
    strcpy(str->str, s);
    str->len = l;
    str->sp = l;
  } else {
    str->str[0] = 0;
    str->len = 0;
  }
  return DohObjMalloc(&DohStringType, str);
}
