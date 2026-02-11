repair_loop_structures (void)
{
  bitmap changed_bbs;

  timevar_push (TV_REPAIR_LOOPS);
  changed_bbs = BITMAP_ALLOC (NULL);
  fix_loop_structure (changed_bbs);


  if (loops_state_satisfies_p (LOOP_CLOSED_SSA))
    rewrite_into_loop_closed_ssa (changed_bbs, TODO_update_ssa);

  BITMAP_FREE (changed_bbs);

#ifdef ENABLE_CHECKING
  verify_loop_structure ();
#endif
  scev_reset ();

  loops_state_clear (LOOPS_NEED_FIXUP);
  timevar_pop (TV_REPAIR_LOOPS);
}
