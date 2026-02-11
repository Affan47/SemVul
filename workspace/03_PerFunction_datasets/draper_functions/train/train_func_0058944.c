add_shape_value(int pos, float value)
{
  ASSERT_ON_BOARD1(pos);
  if (value > 0.0) {
    if (value > move[pos].maxpos_shape)
      move[pos].maxpos_shape = value;
    move[pos].numpos_shape += 1;
  }
  else if (value < 0.0) {
    value = -value;
    if (value > move[pos].maxneg_shape)
      move[pos].maxneg_shape = value;
    move[pos].numneg_shape += 1;
  }
}
