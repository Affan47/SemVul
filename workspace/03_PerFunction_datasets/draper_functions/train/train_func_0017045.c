SetVectorContents(char* chars,
                                            int size,
                                            bool* exists) {
  if (!chars) {
    *exists = false;
    return Vector<const char>::empty();
  }
  chars[size] = '\0';
  *exists = true;
  return Vector<const char>(chars, size);
}
