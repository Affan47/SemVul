gen_dequeue(void* arg)
{
  struct GenHeader* gen = (struct GenHeader*) arg;

  if (gen->gh_next)
    gen->gh_next->gh_prev_p = gen->gh_prev_p;
  if (gen->gh_prev_p)
    *gen->gh_prev_p = gen->gh_next;

  gen->gh_next = 0;
  gen->gh_prev_p = 0;
}
