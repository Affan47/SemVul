count_terrain_near_tile(const struct tile *ptile,
			    bool cardinal_only, bool percentage,
			    const struct terrain *pterrain)
{
  int count = 0, total = 0;

  variable_adjc_iterate(ptile, adjc_tile, cardinal_only) {
    if (pterrain && tile_terrain(adjc_tile) == pterrain) {
      count++;
    }
    total++;
  } variable_adjc_iterate_end;

  if (percentage) {
    count = count * 100 / total;
  }
  return count;
}
