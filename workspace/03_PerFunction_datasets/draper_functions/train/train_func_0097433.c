board_count_diff_winner_get_empties (const Board *const b,
                                     const Player p)
{
  g_assert(b);
  g_assert(p == BLACK_PLAYER || p == WHITE_PLAYER);

  int pcount, ocount, difference, empties;
  Player o;

  o = player_opponent(p);
  pcount = board_count_pieces(b, player_color(p));
  ocount = board_count_pieces(b, player_color(o));

  difference = pcount - ocount;
  empties = 64 - (pcount + ocount);

  return difference + ((difference > 0) ? +empties : -empties);
}
