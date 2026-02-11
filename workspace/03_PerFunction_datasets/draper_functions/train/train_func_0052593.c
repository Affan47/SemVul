game_position_x_compare (const GamePositionX *const a,
                         const GamePositionX *const b)
{
  g_assert(a);
  g_assert(b);

  if (a == b) return 0;

  if (a->blacks < b->blacks) {
    return -1;
  } else if (a->blacks > b->blacks) {
    return +1;
  } else {
    if (a->whites < b->whites) {
      return -1;
    } else if (a->whites > b->whites) {
      return +1;
    } else {
      if (a->player < b->player) {
        return -1;
      } else if (a->player > b->player) {
        return +1;
      } else {
        return 0;
      }
    }
  }
}
