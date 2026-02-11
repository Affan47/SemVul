tree_unroll_loops_completely_1 (bool may_increase_size, bool unroll_outer,
				vec<loop_p, va_stack>& father_stack,
				struct loop *loop)
{
  struct loop *loop_father;
  bool changed = false;
  struct loop *inner;
  enum unroll_level ul;


  for (inner = loop->inner; inner != NULL; inner = inner->next)
    changed |= tree_unroll_loops_completely_1 (may_increase_size,
					       unroll_outer, father_stack,
					       inner);


  if (changed)
    return true;


  loop_father = loop_outer (loop);
  if (!loop_father)
    return false;

  if (may_increase_size && optimize_loop_nest_for_speed_p (loop)


      && (unroll_outer || loop_outer (loop_father)))
    ul = UL_ALL;
  else
    ul = UL_NO_GROWTH;

  if (canonicalize_loop_induction_variables
        (loop, false, ul, !flag_tree_loop_ivcanon))
    {


      if (loop_outer (loop_father) && !loop_father->aux)
	{
	  father_stack.safe_push (loop_father);
	  loop_father->aux = loop_father;
	}

      return true;
    }

  return false;
}
