GWEN_Text_StrCaseStr(const char *haystack, const char *needle) {
  while(*haystack) {
    while(*haystack && tolower(*haystack)!=tolower(*needle))
      haystack++;
    if (*haystack) {
      const char *t;
      const char *s;


      t=haystack;
      s=needle;
      t++;
      s++;
      while(*t && *s && (tolower(*t)==tolower(*s))) {
	t++;
	s++;
      }
      if (*s==0)
	return haystack;
    }
    else

      break;

    haystack++;
  }


  return NULL;
}
