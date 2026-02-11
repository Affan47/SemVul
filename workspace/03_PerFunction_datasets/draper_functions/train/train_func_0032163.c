circuit(Home home, const IntArgs& c, int offset,
          const IntVarArgs& x, const IntVarArgs& y, IntVar z,
          IntConLevel icl) {
    Int::Limits::nonnegative(offset,"Int::circuit");
    int n = x.size();
    if (n == 0)
      throw Int::TooFewArguments("Int::circuit");
    if (x.same(home))
      throw Int::ArgumentSame("Int::circuit");
    if ((y.size() != n) || (c.size() != n*n))
      throw Int::ArgumentSizeMismatch("Int::circuit");
    circuit(home, offset, x, icl);
    if (home.failed()) return;
    IntArgs cx(offset+n);
    for (int i=0; i<offset; i++)
      cx[i] = 0;
    for (int i=n; i--; ) {
      for (int j=0; j<n; j++)
        cx[offset+j] = c[i*n+j];
      element(home, cx, x[i], y[i]);
    }
    linear(home, y, IRT_EQ, z);
  }
