find_common_loop (loop_s, loop_d)
    struct loop *loop_s;
    struct loop *loop_d;
{
  if (!loop_s) return loop_d;
  if (!loop_d) return loop_s;

  if (loop_s->depth < loop_d->depth)
    loop_d = loop_d->pred[loop_s->depth];
  else if (loop_s->depth > loop_d->depth)
    loop_s = loop_s->pred[loop_d->depth];

  while (loop_s != loop_d)
    {
      loop_s = loop_s->outer;
      loop_d = loop_d->outer;
    }
  return loop_s;
}
