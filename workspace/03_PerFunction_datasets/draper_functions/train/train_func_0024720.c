autohelperowl_vital_apat44(int trans, int move, int color, int action)
{
  int a, b, c;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(683, trans, move);
  b = AFFINE_TRANSFORM(721, trans, move);
  c = AFFINE_TRANSFORM(685, trans, move);

  return  owl_proper_eye(move) && (owl_proper_eye(a) + owl_proper_eye(b) + owl_proper_eye(c) > 2) && safe_move(move, OTHER_COLOR(color)) && ((owl_eye_size(move) <= 8 && owl_maxeye(move)>1) || !play_attack_defend_n(color, 1, 1, move, move));
}
