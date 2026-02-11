fl_width(const char* c) {
  if (c) return fl_width(c, strlen(c));
  else return 0.0f;
}
