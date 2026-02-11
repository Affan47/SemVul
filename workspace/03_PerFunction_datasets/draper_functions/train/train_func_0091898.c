parseOr(Owner<Expression> &expr)
{
  Location loc(in_->currentLocation());
  Token tok;
  Identifier::SyntacticKey key;
  Owner<Expression> test1Expr;
  if (!parseExpression(allowCloseParen, test1Expr, key, tok))
    return 0;
  if (!test1Expr) {
    expr = new ConstantExpression(interp_->makeFalse(), loc);
    return 1;
  }
  Owner<Expression> test2Expr;
  if (!parseOr(test2Expr))
    return 0;
  expr = new OrExpression(test1Expr, test2Expr, loc);
  return 1;
}
