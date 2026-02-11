arg2intargs(AST::Node* arg, int offset) {
    AST::Array* a = arg->getArray();
    IntArgs ia(a->a.size()+offset);
    for (int i=offset; i--;)
      ia[i] = 0;
    for (int i=a->a.size(); i--;)
      ia[i+offset] = a->a[i]->getInt();
    return ia;
  }
