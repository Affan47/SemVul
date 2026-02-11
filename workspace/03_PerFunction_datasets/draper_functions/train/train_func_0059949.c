parseRuleBody(Owner<Expression> &expr, ProcessingMode::RuleType &ruleType)
{
  Token tok;
  Identifier::SyntacticKey key;
  if (!parseExpression(0, expr, key, tok))
    return 0;
  const Identifier *k = dsssl2() ? expr->keyword() : 0;
  if (k) {

    Vector<const Identifier *> keys;
    NCVector<Owner<Expression> > exprs;
    for (;;) {
      keys.push_back(k);
      exprs.resize(exprs.size() + 1);
      if (!parseExpression(0, exprs.back(), key, tok))
        return 0;
      if (!getToken(allowKeyword|allowCloseParen, tok))
	return 0;
      if (tok == tokenCloseParen)
	break;
      k = lookup(currentToken_);
    }
    expr = new StyleExpression(keys, exprs, expr->location());
    ruleType = ProcessingMode::styleRule;
  }
  else {
    ruleType = ProcessingMode::constructionRule;
    if (!getToken(allowCloseParen, tok))
      return 0;
  }
  return 1;
}
