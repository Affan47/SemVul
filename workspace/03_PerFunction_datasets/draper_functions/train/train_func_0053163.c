game_position_x_hash (const GamePositionX *const gpx)
{
  const SquareSet whites = gpx->whites;
  const SquareSet blacks = gpx->blacks;
  const Player p = gpx->player;

  uint64_t hash = 0;

  for (int i = 0; i < 64; i++) {
    const uint64_t mask = (uint64_t) 1 << i;
    if (blacks & mask) hash ^= zobrist_bitstrings[i];
    if (whites & mask) hash ^= zobrist_bitstrings[i + 64];
  }
  if (p) hash = ~hash;

  return hash;
}
