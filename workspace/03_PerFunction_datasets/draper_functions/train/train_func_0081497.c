deq(THREAD_Q q, THREAD t) {
  if (!q)
    return;

  if (t->prev_q)
    t->prev_q->next_q = t->next_q;
  else
    q->h = t->next_q;

  if (t->next_q)
    t->next_q->prev_q = t->prev_q;
  else
    q->t = t->prev_q;

  t->queue = NULL;
}
