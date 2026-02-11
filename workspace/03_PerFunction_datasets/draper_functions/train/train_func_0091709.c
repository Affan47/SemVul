autohelperowl_defendpat379(int trans, int move, int color, int action)
{
  int c, d, A, B;
  UNUSED(color);
  UNUSED(action);

  c = AFFINE_TRANSFORM(722, trans, move);
  d = AFFINE_TRANSFORM(720, trans, move);
  A = AFFINE_TRANSFORM(683, trans, move);
  B = AFFINE_TRANSFORM(721, trans, move);

  return owl_escape_value(c)>0 && owl_goal_dragon(d) && !play_attack_defend2_n(color, 0, 1, move, A, B);
}
