StateToWorkq(State* s, Workq* q) {
  q->clear();
  for (int i = 0; i < s->ninst_; i++) {
    if (s->inst_[i] == Mark)
      q->mark();
    else
      q->insert_new(s->inst_[i]);
  }
}
