findchar_backward(int startPos, unsigned int searchChar,
				      int *foundPos) const {
  if (startPos <= 0) {
    *foundPos = 0;
    return 0;
  }

  if (startPos > mLength)
    startPos = mLength;

  for (startPos = prev_char(startPos); startPos>=0; startPos = prev_char(startPos)) {
    if (searchChar == char_at(startPos)) {
      *foundPos = startPos;
      return 1;
    }
  }

  *foundPos = 0;
  return 0;
}
