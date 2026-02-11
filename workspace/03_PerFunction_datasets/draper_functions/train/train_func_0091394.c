convtolower(char *catbuff, const char *a) {
  strcpybuff(catbuff, a);
  hts_lowcase(catbuff);
  return catbuff;
}
