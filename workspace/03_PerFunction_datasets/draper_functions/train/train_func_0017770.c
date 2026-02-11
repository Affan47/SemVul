TryCallApply(Call* expr) {
  Expression* callee = expr->expression();
  Property* prop = callee->AsProperty();
  ASSERT(prop != NULL);

  if (graph()->info()->scope()->arguments() == NULL) return false;

  Handle<String> name = prop->key()->AsLiteral()->AsPropertyName();
  if (!name->IsEqualTo(CStrVector("apply"))) return false;

  ZoneList<Expression*>* args = expr->arguments();
  if (args->length() != 2) return false;

  VariableProxy* arg_two = args->at(1)->AsVariableProxy();
  if (arg_two == NULL || !arg_two->var()->IsStackAllocated()) return false;
  HValue* arg_two_value = environment()->Lookup(arg_two->var());
  if (!arg_two_value->CheckFlag(HValue::kIsArguments)) return false;

  if (!expr->IsMonomorphic() ||
      expr->check_type() != RECEIVER_MAP_CHECK) return false;


  VisitForValue(prop->obj());
  if (HasStackOverflow()) return false;
  HValue* function = Pop();
  VisitForValue(args->at(0));
  if (HasStackOverflow()) return false;
  HValue* receiver = Pop();
  HInstruction* elements = AddInstruction(new HArgumentsElements);
  HInstruction* length = AddInstruction(new HArgumentsLength(elements));
  AddCheckConstantFunction(expr,
                           function,
                           expr->GetReceiverTypes()->first(),
                           true);
  HInstruction* result =
      new HApplyArguments(function, receiver, length, elements);
  result->set_position(expr->position());
  ast_context()->ReturnInstruction(result, expr->id());
  return true;
}
