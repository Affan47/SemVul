getChar() {

  int c = lookChar();
  nextCharBuff = EOF;

  if (c != EOF)
    charactersRead++;
  return c;
}
