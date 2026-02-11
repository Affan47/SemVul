hasPrefix(const String *str, const String *prefix) {
    int len_prefix = Len(prefix);
    return (Len(str) > len_prefix)
	&& (Strncmp(str, prefix, len_prefix) == 0);
  }
