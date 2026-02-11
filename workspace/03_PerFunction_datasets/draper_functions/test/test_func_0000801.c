autohelperbarrierspat176(int trans, int move, int color, int action)
{
  int a, b;
  UNUSED(color);

  a = AFFINE_TRANSFORM(685, trans, move);
  b = AFFINE_TRANSFORM(683, trans, move);

  if (!action)
    return play_attack_defend_n(color, 1, 2, move, a, a) && safe_move(move, color);
  influence_mark_non_territory(move, OTHER_COLOR(color));influence_mark_non_territory(b, OTHER_COLOR(color));;

  return 0;
}
