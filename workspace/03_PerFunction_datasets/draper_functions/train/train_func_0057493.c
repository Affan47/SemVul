arg2IntVar(AST::Node* n) {
    IntVar x0;
    if (n->isIntVar()) {
      x0 = iv[n->getIntVar()];
    } else {
      x0 = IntVar(*this, n->getInt(), n->getInt());
    }
    return x0;
  }
