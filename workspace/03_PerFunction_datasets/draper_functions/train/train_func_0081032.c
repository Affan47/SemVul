atStartOfLine() const {
  return isValidTextPosition() && column() == 0;
}
