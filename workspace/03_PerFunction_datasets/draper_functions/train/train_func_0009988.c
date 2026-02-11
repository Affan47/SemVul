ParseAssignmentExpression(bool accept_IN, bool* ok) {


  if (fni_ != NULL) fni_->Enter();
  Expression* expression = ParseConditionalExpression(accept_IN, CHECK_OK);

  if (!Token::IsAssignmentOp(peek())) {
    if (fni_ != NULL) fni_->Leave();

    return expression;
  }


  if (expression == NULL || !expression->IsValidLeftHandSide()) {
    Handle<String> type = Factory::invalid_lhs_in_assignment_symbol();
    expression = NewThrowReferenceError(type);
  }

  if (temp_scope_->StrictMode()) {

    CheckStrictModeLValue(expression, "strict_lhs_assignment", CHECK_OK);
  }

  Token::Value op = Next();
  int pos = scanner().location().beg_pos;
  Expression* right = ParseAssignmentExpression(accept_IN, CHECK_OK);


  Property* property = expression ? expression->AsProperty() : NULL;
  if (op == Token::ASSIGN &&
      property != NULL &&
      property->obj()->AsVariableProxy() != NULL &&
      property->obj()->AsVariableProxy()->is_this()) {
    temp_scope_->AddProperty();
  }


  if (property != NULL && right->AsFunctionLiteral() != NULL) {
    right->AsFunctionLiteral()->set_pretenure(true);
  }

  if (fni_ != NULL) {


    if ((op == Token::INIT_VAR
         || op == Token::INIT_CONST
         || op == Token::ASSIGN)
        && (right->AsCall() == NULL)) {
      fni_->Infer();
    }
    fni_->Leave();
  }

  return new Assignment(op, expression, right, pos);
}
