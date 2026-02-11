computeBaseType(const Type& t) {
  const Expr& e = t.getExpr();
  switch(e.getKind()) {
  case ARROW: {
    DebugAssert(e.arity() > 0, "Expected non-empty ARROW");
    vector<Expr> kids;
    for(Expr::iterator i=e.begin(), iend=e.end(); i!=iend; ++i) {
      kids.push_back(getBaseType(Type(*i)).getExpr());
    }
    return Type(Expr(e.getOp(), kids));
  }
  case TYPEDECL: return t;
  default:
    DebugAssert(false,
		"TheoryUF::computeBaseType("+t.toString()+")");
    return t;
  }
}
