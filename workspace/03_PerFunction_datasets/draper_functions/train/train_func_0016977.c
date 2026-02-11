print(const BrancherHandle& bh,
               int a, int i, int n, ostream& o) const {
      const BI& bi = v[bh.id()];
      o << bi.n[i] << " " << (a==0 ? bi.r0 : bi.r1) << " " << n;
    }
