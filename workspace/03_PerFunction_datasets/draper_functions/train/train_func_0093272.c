free_htimer (a_timer timer)
{
  dmsg (D_TIMER, "free timer %p", timer);
  XFREE (timer);
}
