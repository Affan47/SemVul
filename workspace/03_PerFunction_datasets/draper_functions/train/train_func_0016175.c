autohelperowl_attackpat251(int trans, int move, int color, int action)
{
  int a, A, B;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(648, trans, move);
  A = AFFINE_TRANSFORM(686, trans, move);
  B = AFFINE_TRANSFORM(721, trans, move);

  return  play_attack_defend_n(OTHER_COLOR(color), 1, 2, move, a, B) && !play_attack_defend_n(color, 0, 1, move, A);
}
