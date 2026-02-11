add_bonus (int pos_in_list, unsigned char what)
{
  int pos;

  do
    pos = rand () % lvl.tile_count;
  while (tile_bonus[pos] != 0);

  tile_bonus[pos] = what;
  bonus_list[pos_in_list] = pos;
  bonus_time[pos_in_list] = event_time + (rand () % 511) - 256;

  dmsg (D_BONUS, "Add bonus: type=%u, pos=%u, pos_in_list=%u",
	what, pos, pos_in_list);

  --what;

  if (what == 16)
    fg_data[pos].big_dollar = 1;
  else {
    if (what & 128)
      fg_data[pos].bonus = bonus_rle[1][what & 127];
    else
      fg_data[pos].bonus = bonus_rle[0][what];
  }
}
