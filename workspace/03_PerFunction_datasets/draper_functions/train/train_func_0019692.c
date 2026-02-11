VisitArithmeticExpression(BinaryOperation* expr) {
  Token::Value op = expr->op();
  Comment cmnt(masm_, "[ ArithmeticExpression");
  Expression* left = expr->left();
  Expression* right = expr->right();
  OverwriteMode mode =
      left->ResultOverwriteAllowed()
      ? OVERWRITE_LEFT
      : (right->ResultOverwriteAllowed() ? OVERWRITE_RIGHT : NO_OVERWRITE);

  VisitForStackValue(left);
  VisitForAccumulatorValue(right);

  SetSourcePosition(expr->position());
  if (ShouldInlineSmiCase(op)) {
    EmitInlineSmiBinaryOp(expr, op, mode, left, right);
  } else {
    EmitBinaryOp(expr, op, mode);
  }
}
