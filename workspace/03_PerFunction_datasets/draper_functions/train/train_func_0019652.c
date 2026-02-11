ParseInt(const StringPiece& str ) {
  char* errIndex;

  int value = static_cast<int>(strtol(str.data(), &errIndex,10));
  if (errIndex == str.data()) {
    throw util::ParseNumberException(str);
  }
  return value;
}
