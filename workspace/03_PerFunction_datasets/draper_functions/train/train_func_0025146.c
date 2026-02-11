printLit(ostream& os, const Literal& l) {
    if(l.isNegative()) os << "!";
    os << l.getVar().getExpr();
    int val(l.getValue());
    if(val != 0) os << "=" << val << "@" << l.getScope();
  }
