ParseFloat(const StringPiece& str) {
  char* errIndex;
  float value = static_cast<float>(strtod(str.data(), &errIndex));
  if (errIndex == str.data()) {
    throw util::ParseNumberException(str);
  }
  return value;
}
