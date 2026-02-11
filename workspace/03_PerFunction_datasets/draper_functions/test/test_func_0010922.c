optimize_loop (hwloop_info loop, struct hw_doloop_hooks *hooks)
{
  int ix;
  hwloop_info inner;
  int inner_depth = 0;

  if (loop->visited)
    return;

  loop->visited = 1;

  if (loop->bad)
    {
      if (dump_file)
	fprintf (dump_file, ";; loop %d bad when found\n", loop->loop_no);
      goto bad_loop;
    }


  for (ix = 0; loop->loops.iterate (ix, &inner); ix++)
    {
      optimize_loop (inner, hooks);

      if (!inner->bad && inner_depth < inner->depth)
	inner_depth = inner->depth;


      IOR_HARD_REG_SET (loop->regs_set_in_loop, inner->regs_set_in_loop);
    }

  loop->depth = inner_depth + 1;

  if (hooks->opt (loop))
    return;

 bad_loop:
  if (dump_file)
    fprintf (dump_file, ";; loop %d is bad\n", loop->loop_no);

  loop->bad = true;
  hooks->fail (loop);
}
