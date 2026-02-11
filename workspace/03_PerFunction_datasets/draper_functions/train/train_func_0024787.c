propagators(void) const {
    unsigned int n = 0;
    for (Propagators p(*this); p(); ++p)
      n++;
    return n;
  }
