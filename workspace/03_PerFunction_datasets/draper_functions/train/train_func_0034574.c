getExpr() const {
    DebugAssert(!isNull(), "CVC3::Theorem::getExpr(): we are Null");
    if (isRefl()) {
      Expr e(exprValue());
      if (e.isTerm()) return e.eqExpr(e);
      else return e.iffExpr(e);
    }
    else return thm()->getExpr();
  }
