seki_helper(int str)
{
  int r;
  int adj;
  int adjs[MAXCHAIN];

  adj = chainlinks(str, adjs);
  for (r = 0; r < adj; r++)
    if (worm[adjs[r]].attack_codes[0] != 0)
      return 0;

  return 1;
}
