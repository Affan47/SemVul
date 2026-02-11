autohelperowl_defendpat448(int trans, int move, int color, int action)
{
  int a, A, B, C, D;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(757, trans, move);
  A = AFFINE_TRANSFORM(646, trans, move);
  B = AFFINE_TRANSFORM(758, trans, move);
  C = AFFINE_TRANSFORM(720, trans, move);
  D = AFFINE_TRANSFORM(721, trans, move);

  return  (owl_escape_value(A) > 0 || owl_escape_value(B) > 0) && play_connect_n(OTHER_COLOR(color), 0, 0, A, C) && play_attack_defend_n(color, 1, 2, move, a, D);
}
