pythonappend(Node *n) {
    String *str = Getattr(n, "feature:pythonappend");
    if (!str)
      str = Getattr(n, "feature:addtofunc");

    char *t = Char(str);
    if (*t == '{') {
      Delitem(str, 0);
      Delitem(str, DOH_END);
    }
    return str;
  }
