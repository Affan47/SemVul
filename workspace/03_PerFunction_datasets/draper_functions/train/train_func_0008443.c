p_int_CMP_reif(FlatZincSpace& s, IntRelType irt, ReifyMode rm,
                        const ConExpr& ce, AST::Node* ann) {
      if (rm == RM_EQV && ce[2]->isBool()) {
        if (ce[2]->getBool()) {
          p_int_CMP(s, irt, ce, ann);
        } else {
          p_int_CMP(s, neg(irt), ce, ann);
        }
        return;
      }
      if (ce[0]->isIntVar()) {
        if (ce[1]->isIntVar()) {
          rel(s, s.arg2IntVar(ce[0]), irt, s.arg2IntVar(ce[1]),
                 Reify(s.arg2BoolVar(ce[2]), rm), s.ann2icl(ann));
        } else {
          rel(s, s.arg2IntVar(ce[0]), irt, ce[1]->getInt(),
                 Reify(s.arg2BoolVar(ce[2]), rm), s.ann2icl(ann));
        }
      } else {
        rel(s, s.arg2IntVar(ce[1]), swap(irt), ce[0]->getInt(),
               Reify(s.arg2BoolVar(ce[2]), rm), s.ann2icl(ann));
      }
    }
