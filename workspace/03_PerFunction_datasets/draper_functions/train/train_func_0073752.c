rand_neighbour(const struct tile *ptile)
{
  int n;
  struct tile *tile1;


  enum direction8 dirs[8] = {
    DIR8_NORTHWEST, DIR8_NORTH, DIR8_NORTHEAST, DIR8_WEST, DIR8_EAST,
    DIR8_SOUTHWEST, DIR8_SOUTH, DIR8_SOUTHEAST
  };


  for (n = 8; n > 0; n--) {
    enum direction8 choice = (enum direction8) fc_rand(n);


    tile1 = mapstep(ptile, dirs[choice]);
    if (tile1) {
      return tile1;
    }


    dirs[choice] = dirs[n - 1];
  }

  fc_assert(FALSE);
  return NULL;
}
