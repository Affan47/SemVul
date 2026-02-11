ScanLiteralUnicodeEscape() {
  ASSERT(c0_ == '\\');
  uc32 chars_read[6] = {'\\', 'u', 0, 0, 0, 0};
  Advance();
  int i = 1;
  if (c0_ == 'u') {
    i++;
    while (i < 6) {
      Advance();
      if (!IsHexDigit(c0_)) break;
      chars_read[i] = c0_;
      i++;
    }
  }
  if (i < 6) {

    while (i > 0) {
      i--;
      PushBack(chars_read[i]);
    }
    return false;
  }

  for (int i = 0; i < 6; i++) {
    AddLiteralChar(chars_read[i]);
  }
  return true;
}
