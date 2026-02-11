CopyForInlining(Handle<JSFunction> target,
                                            FunctionLiteral* function,
                                            bool is_speculative,
                                            HConstant* undefined) const {

  int arity = function->scope()->num_parameters();
  HEnvironment* outer = Copy();
  outer->Drop(arity + 1);
  outer->ClearHistory();
  HEnvironment* inner = new HEnvironment(outer, function->scope(), target);

  if (is_speculative) {
    for (int i = 0; i <= arity; ++i) {
      HValue* push = ExpressionStackAt(arity - i);
      inner->SetValueAt(i, push);
    }
  } else {
    for (int i = 0; i <= arity; ++i) {
      inner->SetValueAt(i, ExpressionStackAt(arity - i));
    }
  }


  int local_base = arity + 1;
  int local_count = function->scope()->num_stack_slots();
  for (int i = 0; i < local_count; ++i) {
    inner->SetValueAt(local_base + i, undefined);
  }

  inner->set_ast_id(function->id());
  return inner;
}
