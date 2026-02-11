notice(Actor& a, ActorProperty p, bool duplicate) {
    if (p & AP_DISPOSE) {
      if (duplicate && (d_fst != NULL)) {
        for (Actor** f = d_fst; f < d_cur; f++)
          if (&a == *f)
            return;
      }
      if (d_cur == d_lst) {

        if (d_fst == NULL) {

          d_fst = alloc<Actor*>(4);
          d_cur = d_fst;
          d_lst = d_fst+4;
        } else {

          unsigned int n = static_cast<unsigned int>(d_lst - d_fst);
          assert(n != 0);
          d_fst = realloc<Actor*>(d_fst,n,2*n);
          d_cur = d_fst+n;
          d_lst = d_fst+2*n;
        }
      }
      *(d_cur++) = &a;
    } else if (p & AP_WEAKLY) {
      if (wmp() == 0)
        wmp(2);
      else
        wmp(wmp()+1);
    }
  }
