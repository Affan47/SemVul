VisitArgument(Expression* expr) {
  VISIT_FOR_VALUE(expr);
  Push(AddInstruction(new HPushArgument(Pop())));
}
