ParseNewPrefix(PositionStack* stack, bool* ok) {


  Expect(Token::NEW, CHECK_OK);
  PositionStack::Element pos(stack, scanner().location().beg_pos);

  Expression* result;
  if (peek() == Token::NEW) {
    result = ParseNewPrefix(stack, CHECK_OK);
  } else {
    result = ParseMemberWithNewPrefixesExpression(stack, CHECK_OK);
  }

  if (!stack->is_empty()) {
    int last = stack->pop();
    result = new CallNew(result, new ZoneList<Expression*>(0), last);
  }
  return result;
}
