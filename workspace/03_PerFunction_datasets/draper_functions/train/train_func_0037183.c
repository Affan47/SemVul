writePSTextLine(GooString *s) {
  int i, j, step;
  int c;


  if (s->getLength() >= 2 &&
      (s->getChar(0) & 0xff) == 0xfe &&
      (s->getChar(1) & 0xff) == 0xff) {
    i = 3;
    step = 2;
  } else {
    i = 0;
    step = 1;
  }
  for (j = 0; i < s->getLength() && j < 200; i += step) {
    c = s->getChar(i) & 0xff;
    if (c == '\\') {
      writePS("\\\\");
      j += 2;
    } else if (c < 0x20 || c > 0x7e || (j == 0 && c == '(')) {
      writePSFmt("\\{0:03o}", c);
      j += 4;
    } else {
      writePSChar(c);
      ++j;
    }
  }
  writePS("\n");
}
