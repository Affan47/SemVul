board_get_square (const Board *const b,
                  const Square sq)
{
  g_assert(b);
  g_assert(square_belongs_to_enum_set(sq));

  SquareSet bitsquare = (SquareSet) 1 << sq;
  if (bitsquare & b->blacks)
    return BLACK_SQUARE;
  else if (bitsquare & b->whites)
    return WHITE_SQUARE;
  else
    return EMPTY_SQUARE;
}
