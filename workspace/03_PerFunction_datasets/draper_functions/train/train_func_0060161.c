SkipJsonWhiteSpace() {
  int start_position = source_pos();

  while (c0_ == ' ' || c0_ == '\n' || c0_ == '\r' || c0_ == '\t') {
    Advance();
  }
  return source_pos() != start_position;
}
