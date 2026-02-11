p_minimum(FlatZincSpace& s, const ConExpr& ce, AST::Node* ann) {
      IntVarArgs iv = s.arg2intvarargs(ce[1]);
      min(s, iv, s.arg2IntVar(ce[0]), s.ann2icl(ann));
    }
