repeat_timeout(double time, Fl_Timeout_Handler cb, void *argp) {
  time += missed_timeout_by; if (time < -.05) time = 0;
  Timeout* t = free_timeout;
  if (t) {
      free_timeout = t->next;
      --free_timeout_count;
  } else {
      t = new Timeout;
  }
  t->time = time;
  t->cb = cb;
  t->arg = argp;

  Timeout** p = &first_timeout;
  while (*p && (*p)->time <= time) p = &((*p)->next);
  t->next = *p;
  *p = t;
}
