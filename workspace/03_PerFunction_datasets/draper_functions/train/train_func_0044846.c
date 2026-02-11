linear(Home home,
         const IntArgs& a, const BoolVarArgs& x, IntRelType irt, int c,
         Reify r, IntConLevel icl) {
    if (a.size() != x.size())
      throw ArgumentSizeMismatch("Int::linear");
    if (home.failed()) return;

    int n=x.size();
    Region re(home);
    Linear::Term<BoolView>* t = re.alloc<Linear::Term<BoolView> >(n);
    for (int i=n; i--; ) {
      t[i].a=a[i]; t[i].x=x[i];
    }

    Linear::post(home,t,n,irt,c,r,icl);
  }
