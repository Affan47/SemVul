next_worm_in_dragon(int w)
{
  ASSERT1(worm[w].origin == w, w);
  return next_worm_list[w];
}
