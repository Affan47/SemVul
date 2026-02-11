p_nvalue(FlatZincSpace& s, const ConExpr& ce, AST::Node* ann) {
      IntVarArgs x = s.arg2intvarargs(ce[1]);
      if (ce[0]->isIntVar()) {
        IntVar y = s.arg2IntVar(ce[0]);
        nvalues(s,x,IRT_EQ,y,s.ann2icl(ann));
      } else {
        nvalues(s,x,IRT_EQ,ce[0]->getInt(),s.ann2icl(ann));
      }
    }
