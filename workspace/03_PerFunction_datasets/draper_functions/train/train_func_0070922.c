reset() {
  short code1;

  unfilteredReset();

  if (codingLine != NULL && refLine != NULL) {
    eof = gFalse;
    codingLine[0] = columns;
  } else {
    eof = gTrue;
  }


  while ((code1 = lookBits(12)) == 0) {
    eatBits(1);
  }
  if (code1 == 0x001) {
    eatBits(12);
  }
  if (encoding > 0) {
    nextLine2D = !lookBits(1);
    eatBits(1);
  }
}
