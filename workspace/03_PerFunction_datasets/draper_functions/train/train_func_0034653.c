p_bool_or_imp(FlatZincSpace& s, const ConExpr& ce, AST::Node* ann) {
      BoolVar b0 = s.arg2BoolVar(ce[0]);
      BoolVar b1 = s.arg2BoolVar(ce[1]);
      BoolVar b2 = s.arg2BoolVar(ce[2]);
      clause(s, BOT_OR, BoolVarArgs()<<b0<<b1, BoolVarArgs()<<b2, 1,
             s.ann2icl(ann));
    }
