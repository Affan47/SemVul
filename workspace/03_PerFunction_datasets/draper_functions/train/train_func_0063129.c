doIncCharCount(GooString *s) {
  if (out->needCharCount()) {
    out->incCharCount(s->getLength());
  }
}
