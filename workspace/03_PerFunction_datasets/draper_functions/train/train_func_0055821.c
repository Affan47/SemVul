encode(int c) {
    for (int i=7; i>=0; --i)
      e.encode((c>>i)&1);
  }
