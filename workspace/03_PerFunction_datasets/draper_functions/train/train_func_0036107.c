MarkAsDeoptimizingRecursively(HBasicBlock* block) {
  for (int i = 0; i < block->dominated_blocks()->length(); ++i) {
    HBasicBlock* dominated = block->dominated_blocks()->at(i);
    if (block->IsDeoptimizing()) dominated->MarkAsDeoptimizing();
    MarkAsDeoptimizingRecursively(dominated);
  }
}
