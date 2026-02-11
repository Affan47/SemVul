merge(TextWord *word) {
  int i;

  if (word->xMin < xMin) {
    xMin = word->xMin;
  }
  if (word->yMin < yMin) {
    yMin = word->yMin;
  }
  if (word->xMax > xMax) {
    xMax = word->xMax;
  }
  if (word->yMax > yMax) {
    yMax = word->yMax;
  }
  if (len + word->len > size) {
    size = len + word->len;
    text = (Unicode *)greallocn(text, size, sizeof(Unicode));
    charcode = (CharCode *)greallocn(charcode, (size + 1), sizeof(CharCode));
    edge = (double *)greallocn(edge, (size + 1), sizeof(double));
    charPos = (int *)greallocn(charPos, size + 1, sizeof(int));
    font = (TextFontInfo **)greallocn(font, size, sizeof(TextFontInfo *));
    textMat = (Matrix *)greallocn(textMat, size, sizeof(Matrix));
  }
  for (i = 0; i < word->len; ++i) {
    text[len + i] = word->text[i];
    charcode[len + i] = word->charcode[i];
    edge[len + i] = word->edge[i];
    charPos[len + i] = word->charPos[i];
    font[len + i] = word->font[i];
    textMat[len + i] = word->textMat[i];
  }
  edge[len + word->len] = word->edge[word->len];
  charPos[len + word->len] = word->charPos[word->len];
  len += word->len;
}
