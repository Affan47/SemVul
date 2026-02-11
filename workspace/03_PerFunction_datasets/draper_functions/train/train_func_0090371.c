p_circuit(FlatZincSpace& s, const ConExpr& ce, AST::Node *ann) {
      int off = ce[0]->getInt();
      IntVarArgs xv = s.arg2intvarargs(ce[1]);
      circuit(s,off,xv,s.ann2icl(ann));
    }
