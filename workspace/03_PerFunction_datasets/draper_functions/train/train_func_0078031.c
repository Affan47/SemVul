RemoveRange(void **start, void **end, int N) {
  ASSERT(N > 0);
  lock_.Lock();
  if (N == Static::sizemap()->num_objects_to_move(size_class_) &&
      used_slots_ > 0) {
    int slot = --used_slots_;
    ASSERT(slot >= 0);
    TCEntry *entry = &tc_slots_[slot];
    *start = entry->head;
    *end = entry->tail;
    lock_.Unlock();
    return N;
  }

  int result = 0;
  *start = NULL;
  *end = NULL;

  result = FetchFromOneSpansSafe(N, start, end);
  if (result != 0) {
    while (result < N) {
      int n;
      void* head = NULL;
      void* tail = NULL;
      n = FetchFromOneSpans(N - result, &head, &tail);
      if (!n) break;
      result += n;
      SLL_PushRange(start, head, tail);
    }
  }
  lock_.Unlock();
  return result;
}
