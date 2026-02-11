autohelperowl_defendpat110(int trans, int move, int color, int action)
{
  int a, b, c;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(686, trans, move);
  b = AFFINE_TRANSFORM(685, trans, move);
  c = AFFINE_TRANSFORM(648, trans, move);

  return  countlib(a)>1 && safe_move(b, OTHER_COLOR(color)) && !obvious_false_eye(b, color) && play_attack_defend_n(color, 1, 2, move, b, b) && does_attack(b, c);
}
