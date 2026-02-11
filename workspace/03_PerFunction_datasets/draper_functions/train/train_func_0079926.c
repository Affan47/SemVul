setColor(AnnotColor *new_color) {
  annotLocker();
  delete color;

  if (new_color) {
    Object obj1;
    new_color->writeToObject(xref, &obj1);
    update ("C", &obj1);
    color = new_color;
  } else {
    color = NULL;
  }
  invalidateAppearance();
}
