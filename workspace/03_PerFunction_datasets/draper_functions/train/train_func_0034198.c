MarkIfTrivial(Expression* expr) {
  Variable* var = expr->AsVariableProxy()->AsVariable();
  if (var != NULL &&
      var->IsStackAllocated() &&
      !var->is_arguments() &&
      var->mode() != Variable::CONST &&
      (var->is_this() || !av_.Contains(BitIndex(var)))) {
    expr->AsVariableProxy()->set_is_trivial(true);
  }
}
