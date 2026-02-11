timer_new(const char *text)
{
  int it;

  if ( timer_need_init ) timer_init();

  if ( top_timer > MAX_TIMER )
    {
      for ( it = 0; it < MAX_TIMER; it++ )
	fprintf(stderr, "timer %3d:  %s\n", it, rt[it].text);

      fprintf(stderr, "timer_new: MAX_TIMER too small!\n");
    }

  it = top_timer;
  top_timer++;

  rt[it] = rt_init;
  rt[it].reserved = 1;

  if ( text ) strcpy(rt[it].text, text);

  return (it);
}
