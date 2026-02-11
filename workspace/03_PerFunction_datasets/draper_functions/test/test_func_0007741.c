p_nooverlap(FlatZincSpace& s, const ConExpr& ce, AST::Node *ann) {
      IntVarArgs x0 = s.arg2intvarargs(ce[0]);
      IntVarArgs w = s.arg2intvarargs(ce[1]);
      IntVarArgs y0 = s.arg2intvarargs(ce[2]);
      IntVarArgs h = s.arg2intvarargs(ce[3]);
      if (w.assigned() && h.assigned()) {
        IntArgs iw(w.size());
        for (int i=w.size(); i--;)
          iw[i] = w[i].val();
        IntArgs ih(h.size());
        for (int i=h.size(); i--;)
          ih[i] = h[i].val();
        nooverlap(s,x0,iw,y0,ih,s.ann2icl(ann));
      } else {
        IntVarArgs x1(x0.size()), y1(y0.size());
        for (int i=x0.size(); i--; )
          x1[i] = expr(s, x0[i] + w[i]);
        for (int i=y0.size(); i--; )
          y1[i] = expr(s, y0[i] + h[i]);
        nooverlap(s,x0,w,x1,y0,h,y1,s.ann2icl(ann));
      }
    }
