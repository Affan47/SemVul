p_int_in(FlatZincSpace& s, const ConExpr& ce, AST::Node *) {
      IntSet d = s.arg2intset(ce[1]);
      if (ce[0]->isBoolVar()) {
        IntSetRanges dr(d);
        Iter::Ranges::Singleton sr(0,1);
        Iter::Ranges::Inter<IntSetRanges,Iter::Ranges::Singleton> i(dr,sr);
        IntSet d01(i);
        if (d01.size() == 0) {
          s.fail();
        } else {
          rel(s, s.arg2BoolVar(ce[0]), IRT_GQ, d01.min());
          rel(s, s.arg2BoolVar(ce[0]), IRT_LQ, d01.max());
        }
      } else {
        dom(s, s.arg2IntVar(ce[0]), d);
      }
    }
