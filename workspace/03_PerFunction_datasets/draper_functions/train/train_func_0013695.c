p_among_seq_bool(FlatZincSpace& s, const ConExpr& ce,
                          AST::Node* ann) {
      BoolVarArgs x = s.arg2boolvarargs(ce[0]);
      bool val = ce[1]->getBool();
      int q = ce[2]->getInt();
      int l = ce[3]->getInt();
      int u = ce[4]->getInt();
      IntSet S(val, val);
      sequence(s, x, S, q, l, u, s.ann2icl(ann));
    }
