cardinality(Home home, SetVar s, IntVar x) {
    if (home.failed()) return;
    GECODE_ES_FAIL(Set::Int::Card<Set::SetView>::post(home,s, x));
  }
