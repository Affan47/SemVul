MarkIfNotLive(Expression* expr, List<AstNode*>* stack) {
  if (!expr->is_live()) {
    expr->mark_as_live();
    stack->Add(expr);
  }
}
