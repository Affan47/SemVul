decode_len(const char *bufcoded) {
    std::string str(bufcoded);
    return (((str.length() + 3) / 4) * 3) + 1;
  }
