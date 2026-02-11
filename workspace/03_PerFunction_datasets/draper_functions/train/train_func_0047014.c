gt_timer_stop(GtTimer *t)
{
  gt_assert(t);
  if (t->state == TIMER_RUNNING) {
    gettimeofday(&t->stop_tv, NULL);
    gt_xgetrusage(RUSAGE_SELF, &t->stop_ru);
    t->state = TIMER_STOPPED;
  }
}
