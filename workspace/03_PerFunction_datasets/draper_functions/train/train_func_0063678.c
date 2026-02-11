Pi_h_alpha(const baseFElement & K,KN_<double> & v) const
    {
      int k0=0;
      for (int i=0;i<k;i++) {

          int n=teb[i]->pij_alpha.N();
          KN_<R> sv(v(SubArray(n,k0)));
          teb[i]->Pi_h_alpha(K,sv);
          k0+= n;}
      assert(pij_alpha.N()==k0);
    }
