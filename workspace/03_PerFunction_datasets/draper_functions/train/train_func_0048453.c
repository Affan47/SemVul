gimple_duplicate_loop_to_header_edge (struct loop *loop, edge e,
				    unsigned int ndupl, sbitmap wont_exit,
				    edge orig, VEC (edge, heap) **to_remove,
				    int flags)
{
  unsigned first_new_block;

  if (!loops_state_satisfies_p (LOOPS_HAVE_SIMPLE_LATCHES))
    return false;
  if (!loops_state_satisfies_p (LOOPS_HAVE_PREHEADERS))
    return false;

#ifdef ENABLE_CHECKING
  if (loops_state_satisfies_p (LOOP_CLOSED_SSA))
    verify_loop_closed_ssa (true);
#endif

  first_new_block = last_basic_block;
  if (!duplicate_loop_to_header_edge (loop, e, ndupl, wont_exit,
				      orig, to_remove, flags))
    return false;


  flush_pending_stmts (e);


  copy_phi_node_args (first_new_block);

  scev_reset ();

  return true;
}
