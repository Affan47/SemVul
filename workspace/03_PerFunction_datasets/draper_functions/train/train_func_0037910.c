tree_ssa_loop_init (void)
{
  loop_optimizer_init (LOOPS_NORMAL
		       | LOOPS_HAVE_RECORDED_EXITS);
  rewrite_into_loop_closed_ssa (NULL, TODO_update_ssa);


  scev_initialize ();

  if (number_of_loops () <= 1)
    return 0;

  return 0;
}
