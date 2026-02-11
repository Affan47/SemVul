skipSOP() {
  int i;


  if (byteCount >= 6 &&
      bufStr->lookChar(0) == 0xff &&
      bufStr->lookChar(1) == 0x91) {
    for (i = 0; i < 6; ++i) {
      bufStr->getChar();
    }
    byteCount -= 6;
    bitBufLen = 0;
    bitBufSkip = gFalse;
  }
}
