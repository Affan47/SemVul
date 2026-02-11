__sigsuspend_nocancel (set)
     const sigset_t *set;
{
  return do_sigsuspend (set);
}
