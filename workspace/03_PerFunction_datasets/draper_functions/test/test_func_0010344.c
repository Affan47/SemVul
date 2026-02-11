outermost_indep_loop (struct loop *outer, struct loop *loop, mem_ref_p ref)
{
  struct loop *aloop;

  if (bitmap_bit_p (ref->stored, loop->num))
    return NULL;

  for (aloop = outer;
       aloop != loop;
       aloop = superloop_at_depth (loop, loop_depth (aloop) + 1))
    if (!bitmap_bit_p (ref->stored, aloop->num)
	&& ref_indep_loop_p (aloop, ref))
      return aloop;

  if (ref_indep_loop_p (loop, ref))
    return loop;
  else
    return NULL;
}
