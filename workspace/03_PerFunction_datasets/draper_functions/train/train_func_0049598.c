can_sm_ref_p (struct loop *loop, mem_ref_p ref)
{
  tree base;


  if (!bitmap_bit_p (ref->stored, loop->num))
    return false;


  if (!is_gimple_reg_type (TREE_TYPE (ref->mem))
      || TREE_THIS_VOLATILE (ref->mem)
      || !for_each_index (&ref->mem, may_move_till, loop))
    return false;


  if (tree_could_throw_p (ref->mem))
    return false;


  base = get_base_address (ref->mem);
  if ((tree_could_trap_p (ref->mem)
       || (DECL_P (base) && TREE_READONLY (base)))
      && !ref_always_accessed_p (loop, ref, true))
    return false;


  if (!ref_indep_loop_p (loop, ref))
    return false;

  return true;
}
