operator[](int n) {
    if (n < 0)
      return XMLNode();
    if (n >= nodes_.size())
      return XMLNode();
    return *nodes_[n];
  }
