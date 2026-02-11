scev_reset (void)
{
  loop_iterator li;
  struct loop *loop;

  scev_reset_htab ();

  if (!current_loops)
    return;

  FOR_EACH_LOOP (li, loop, 0)
    {
      loop->nb_iterations = NULL_TREE;
    }
}
