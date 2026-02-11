p_member_bool_reif(FlatZincSpace& s, const ConExpr& ce,
                            AST::Node* ann) {
      BoolVarArgs x = s.arg2boolvarargs(ce[0]);
      BoolVar y = s.arg2BoolVar(ce[1]);
      member(s,x,y,s.arg2BoolVar(ce[2]),s.ann2icl(ann));
    }
