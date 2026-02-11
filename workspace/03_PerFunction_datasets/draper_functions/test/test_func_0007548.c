encode(char *encoded, const char *string, int len) {
    std::string str(string, len);
    strncpy(encoded, encode(str).c_str(), str.length());
    return 0;
  }
