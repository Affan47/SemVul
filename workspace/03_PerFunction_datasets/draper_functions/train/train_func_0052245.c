p_distinct(FlatZincSpace& s, const ConExpr& ce, AST::Node* ann) {
      IntVarArgs va = s.arg2intvarargs(ce[0]);
      IntConLevel icl = s.ann2icl(ann);
      distinct(s, va, icl == ICL_DEF ? ICL_BND : icl);
    }
