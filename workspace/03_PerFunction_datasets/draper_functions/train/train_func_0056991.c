DoBasicBlock(HBasicBlock* block, HBasicBlock* next_block) {
  ASSERT(is_building());
  current_block_ = block;
  next_block_ = next_block;
  if (block->IsStartBlock()) {
    block->UpdateEnvironment(graph_->start_environment());
    argument_count_ = 0;
  } else if (block->predecessors()->length() == 1) {


    ASSERT(block->phis()->length() == 0);
    HBasicBlock* pred = block->predecessors()->at(0);
    HEnvironment* last_environment = pred->last_environment();
    ASSERT(last_environment != NULL);

    if (pred->end()->SecondSuccessor() == NULL) {
      ASSERT(pred->end()->FirstSuccessor() == block);
    } else {
      if (pred->end()->FirstSuccessor()->block_id() > block->block_id() ||
          pred->end()->SecondSuccessor()->block_id() > block->block_id()) {
        last_environment = last_environment->Copy();
      }
    }
    block->UpdateEnvironment(last_environment);
    ASSERT(pred->argument_count() >= 0);
    argument_count_ = pred->argument_count();
  } else {

    HBasicBlock* pred = block->predecessors()->at(0);

    HEnvironment* last_environment = pred->last_environment();
    for (int i = 0; i < block->phis()->length(); ++i) {
      HPhi* phi = block->phis()->at(i);
      last_environment->SetValueAt(phi->merged_index(), phi);
    }
    for (int i = 0; i < block->deleted_phis()->length(); ++i) {
      last_environment->SetValueAt(block->deleted_phis()->at(i),
                                   graph_->GetConstantUndefined());
    }
    block->UpdateEnvironment(last_environment);

    argument_count_ = pred->argument_count();
  }
  HInstruction* current = block->first();
  int start = chunk_->instructions()->length();
  while (current != NULL && !is_aborted()) {

    if (!current->EmitAtUses()) {
      VisitInstruction(current);
    }
    current = current->next();
  }
  int end = chunk_->instructions()->length() - 1;
  if (end >= start) {
    block->set_first_instruction_index(start);
    block->set_last_instruction_index(end);
  }
  block->set_argument_count(argument_count_);
  next_block_ = NULL;
  current_block_ = NULL;
}
