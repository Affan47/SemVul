find_next(unsigned Prev) const {
      int Next = BitVector::find_next(v2x(Prev));
      if (Next < 0)
        return 0;
      return x2v(Next);
    }
