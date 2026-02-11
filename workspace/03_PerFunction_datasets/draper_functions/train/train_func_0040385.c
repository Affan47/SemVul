IsAuthTag(const char * str, size_t len) {
    if (str[0] == '<' && str[1] == 'a' &&
                         str[2] == 'u' &&
                         str[3] == 't' &&
                         str[4] == 'h' &&
                         str[5] <= ' ') {
      std::string tag(str, len);

      if (tag.find("mechanism") != std::string::npos)
        return true;
    }
    return false;
  }
