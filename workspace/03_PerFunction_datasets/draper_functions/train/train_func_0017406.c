CopyName(const char* name, int name_size) {
    char* result = NewArray<char>(name_size + 1);
    for (int i = 0; i < name_size; ++i) {
      char c = name[i];
      if (c == '\0') c = ' ';
      result[i] = c;
    }
    result[name_size] = '\0';
    return result;
  }
