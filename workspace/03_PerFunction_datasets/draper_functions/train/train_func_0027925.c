results_wanted(jit_State *J)
{
  TValue *frame = J->L->base-1;
  if (frame_islua(frame))
    return (ptrdiff_t)bc_b(frame_pc(frame)[-1]) - 1;
  else
    return -1;
}
