InitializeReachingDefinitions(int definition_count,
                                              List<BitVector*>* variables,
                                              WorkList<Node>* worklist,
                                              bool mark) {
  ASSERT(!IsMarkedWith(mark));
  int instruction_count = instructions_.length();
  int variable_count = variables->length();

  rd_.Initialize(definition_count);


  if (predecessor_ == NULL) {
    for (int i = 0; i < variable_count; i++) rd_.rd_in()->Add(i);
  }

  for (int i = 0; i < instruction_count; i++) {
    Expression* expr = instructions_[i]->AsExpression();
    if (expr == NULL) continue;
    Variable* var = expr->AssignedVariable();
    if (var == NULL || !var->IsStackAllocated()) continue;


    BitVector* def_set =
        variables->at(ReachingDefinitions::IndexFor(var, variable_count));
    rd_.kill()->Union(*def_set);


    rd_.gen()->Subtract(*def_set);


    rd_.gen()->Add(expr->num());
  }


  if (predecessor_ != NULL) {
    MarkWith(mark);
    worklist->Insert(this);
  }
}
