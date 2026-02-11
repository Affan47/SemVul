concreteExpr(const CVC3::Expr& e, const Lit& literal){
  if ( e.isTrue() || e.isFalse() ||
       (e.isNot() && (e[0].isTrue() || e[0].isFalse())))
    return e;
  else
    return concreteLit(literal);
}
