autohelperaa_attackpat27(int trans, int move, int color, int action)
{
  int a, A, B, C;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(721, trans, move);
  A = AFFINE_TRANSFORM(647, trans, move);
  B = AFFINE_TRANSFORM(685, trans, move);
  C = AFFINE_TRANSFORM(683, trans, move);

  return  countlib(B) <= 5 && countlib(A) > countlib(B) && !play_attack_defend_n(color, 0, 3, move, NO_MOVE, a, C);
}
