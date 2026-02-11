copy(int clipboard) {
  int b = position();
  int e = mark();
  if (b != e) {
    if (b > e) {b = mark(); e = position();}
    if (input_type() == FL_SECRET_INPUT) e = b;
    Fl::copy(value()+b, e-b, clipboard);
    return 1;
  }
  return 0;
}
