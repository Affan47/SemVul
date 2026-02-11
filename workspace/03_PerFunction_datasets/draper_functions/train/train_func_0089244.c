linear(Home home,
         const IntVarArgs& x, IntRelType irt, int c, Reify r,
         IntConLevel) {
    if (home.failed()) return;
    Region re(home);
    Linear::Term<IntView>* t = re.alloc<Linear::Term<IntView> >(x.size());
    for (int i = x.size(); i--; ) {
      t[i].a=1; t[i].x=x[i];
    }
    Linear::post(home,t,x.size(),irt,c,r);
  }
