post(Home home) const {
    Region r(home);
    SetVar s(home,IntSet::empty,
             IntSet(Set::Limits::min,Set::Limits::max));
    NNF::nnf(r,n,false)->post(home,SRT_EQ,s);
    return s;
  }
