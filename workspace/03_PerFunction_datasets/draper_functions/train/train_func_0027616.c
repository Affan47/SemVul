linear(Home home,
         const IntArgs& a, const IntVarArgs& x, IntRelType irt, int c,
         IntConLevel icl) {
    if (a.size() != x.size())
      throw ArgumentSizeMismatch("Int::linear");
    if (home.failed()) return;
    Region re(home);
    Linear::Term<IntView>* t = re.alloc<Linear::Term<IntView> >(x.size());
    for (int i = x.size(); i--; ) {
      t[i].a=a[i]; t[i].x=x[i];
    }
    Linear::post(home,t,x.size(),irt,c,icl);
  }
