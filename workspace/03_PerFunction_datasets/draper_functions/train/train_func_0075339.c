VisitAssignment(Assignment* expr) {


  Variable* var = expr->target()->AsVariableProxy()->AsVariable();
  Property* prop = expr->target()->AsProperty();
  if (prop != NULL || (var != NULL && var->is_global())) {
    is_breakable_ = true;
    return;
  }


  Visit(expr->value());
}
