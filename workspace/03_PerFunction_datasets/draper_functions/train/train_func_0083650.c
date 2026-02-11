ParsePostfixExpression(bool* ok) {


  i::Scanner::Location before = scanner_->peek_location();
  Expression expression = ParseLeftHandSideExpression(CHECK_OK);
  if (!scanner_->HasAnyLineTerminatorBeforeNext() &&
      i::Token::IsCountOp(peek())) {
    if (strict_mode() && expression.IsIdentifier() &&
        expression.AsIdentifier().IsEvalOrArguments()) {
      i::Scanner::Location after = scanner_->location();
      ReportMessageAt(before.beg_pos, after.end_pos,
                      "strict_lhs_postfix", NULL);
      *ok = false;
      return Expression::Default();
    }
    Next();
    return Expression::Default();
  }
  return expression;
}
