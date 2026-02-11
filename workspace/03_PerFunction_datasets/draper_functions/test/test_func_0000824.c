ltrim(string tmpstr) {
  unsigned int i = 0;
  while (i < tmpstr.length() && (tmpstr[i] == ' ' || tmpstr[i] == '\t' || tmpstr[i] == '\r' || tmpstr[i] == '\n')) ++i;
  return i > 0 ? tmpstr.substr(i, tmpstr.length()-i) : tmpstr;
}
