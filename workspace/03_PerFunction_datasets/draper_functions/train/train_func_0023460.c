VisitIfStatement(IfStatement* node) {
  node->condition()->set_no_negative_zero(true);
  Visit(node->condition());
  Visit(node->then_statement());
  if (node->HasElseStatement()) {
    Visit(node->else_statement());
  }
}
