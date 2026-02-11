SyncRange(int begin, int end) {
  ASSERT(begin >= 0);
  ASSERT(end < element_count());


  int start = Min(begin, stack_pointer_ + 1);
  int end_or_stack_pointer = Min(stack_pointer_, end);


  int i = start;

  while (i <= end_or_stack_pointer) {
    if (!elements_[i].is_synced()) SyncElementBelowStackPointer(i);
    i++;
  }
  while (i <= end) {
    SyncElementByPushing(i);
    i++;
  }
}
