find_loop_nest_1 (struct loop *loop, vec<loop_p> *loop_nest)
{


  if (loop->next)
    return false;

  loop_nest->safe_push (loop);
  if (loop->inner)
    return find_loop_nest_1 (loop->inner, loop_nest);
  return true;
}
