isEqualTo(char* s) {
    return size() == strlen(s) && strncmp(s, head_, size()) == 0;
  }
