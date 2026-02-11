LLA_SkiplistDelete(AllocList *head, AllocList *e,
                               AllocList **prev) {
  AllocList *found = LLA_SkiplistSearch(head, e, prev);
  RAW_CHECK(e == found, "element not in freelist");
  for (int i = 0; i != e->levels && prev[i]->next[i] == e; i++) {
    prev[i]->next[i] = e->next[i];
  }
  while (head->levels > 0 && head->next[head->levels - 1] == 0) {
    head->levels--;
  }
}
