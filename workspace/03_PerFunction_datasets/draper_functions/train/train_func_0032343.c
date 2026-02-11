LoopNestingDepth() const {
  const HBasicBlock* current = this;
  int result  = (current->IsLoopHeader()) ? 1 : 0;
  while (current->parent_loop_header() != NULL) {
    current = current->parent_loop_header();
    result++;
  }
  return result;
}
