parseIf(Owner<Expression> &expr)
{
  Location loc(in_->currentLocation());
  Owner<Expression> expr0, expr1, expr2;
  Token tok;
  Identifier::SyntacticKey key;
  if (!parseExpression(0, expr0, key, tok)
      || !parseExpression(0, expr1, key, tok)
      || !parseExpression(dsssl2() ? allowCloseParen : 0, expr2, key, tok))
    return 0;
  if (!expr2)
    expr2 = new ConstantExpression(interp_->makeUnspecified(), in_->currentLocation());
  else if (!getToken(allowCloseParen, tok))
    return 0;
  expr = new IfExpression(expr0, expr1, expr2, loc);
  return 1;
}
