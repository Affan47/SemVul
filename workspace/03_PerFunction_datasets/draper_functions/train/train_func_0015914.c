Indentation() {
  for (int i = 0; i < indentation; i++) {
    outputStream << INDENT;
  }
  return *this;
}
