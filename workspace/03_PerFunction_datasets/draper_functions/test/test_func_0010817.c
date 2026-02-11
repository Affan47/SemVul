decodeHex1(char a) {
  if (a >= '0' && a <= '9')
    return a - '0';
  if (a >= 'A' && a <= 'F')
    return a - 'A' + 10;
  if (a >= 'a' && a <= 'f')
    return a - 'a' + 10;
  throw Fehler("%s",_("Hex number expected"));
}
