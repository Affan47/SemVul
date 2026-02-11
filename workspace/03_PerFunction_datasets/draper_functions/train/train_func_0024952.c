mc_countstones(struct mc_board *mc, int str, int maxstones)
{
  int stone = str;
  int num_stones = 0;
  do {
    num_stones++;
    stone = mc->next_stone[stone];
  } while (stone != str && num_stones < maxstones);

  return num_stones;
}
