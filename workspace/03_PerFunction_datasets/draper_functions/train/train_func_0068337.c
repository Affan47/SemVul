PrintManglingSuffix(raw_ostream &OS, ImmPredicateSet &ImmPredicates,
                           bool StripImmCodes = false) const {
    for (unsigned i = 0, e = Operands.size(); i != e; ++i)
      Operands[i].printManglingSuffix(OS, ImmPredicates, StripImmCodes);
  }
