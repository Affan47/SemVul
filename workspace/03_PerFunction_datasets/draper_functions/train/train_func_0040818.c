have(Value c) {
        Value * i = data.pbegin();
        Value * end = data.pend();
        for (; i != end && *i != c; ++i);
        return i != end;
      }
