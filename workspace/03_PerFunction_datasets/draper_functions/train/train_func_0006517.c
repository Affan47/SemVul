PaintContains(PRectangle rc) {
  bool contains = true;
  if (paintState == painting) {
    if (!rcPaint.Contains(rc)) {
      contains = false;
    }
  }
  return contains;
}
