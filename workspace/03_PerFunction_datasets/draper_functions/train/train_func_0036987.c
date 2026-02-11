CreateSimulate(int ast_id) {
  ASSERT(HasEnvironment());
  HEnvironment* environment = last_environment();
  ASSERT(ast_id == AstNode::kNoNumber ||
         environment->closure()->shared()->VerifyBailoutId(ast_id));

  int push_count = environment->push_count();
  int pop_count = environment->pop_count();

  HSimulate* instr = new(zone()) HSimulate(ast_id, pop_count);
  for (int i = push_count - 1; i >= 0; --i) {
    instr->AddPushedValue(environment->ExpressionStackAt(i));
  }
  for (int i = 0; i < environment->assigned_variables()->length(); ++i) {
    int index = environment->assigned_variables()->at(i);
    instr->AddAssignedValue(index, environment->Lookup(index));
  }
  environment->ClearHistory();
  return instr;
}
