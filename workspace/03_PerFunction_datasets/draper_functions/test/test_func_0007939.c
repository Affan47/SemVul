random_unchecked_direction(int possibilities, const bool *checked)
{
  int j = -1;
  int i;

  int num = fc_rand(possibilities);
  for (i = 0; i <= num; i++) {
    j++;
    while (checked[j]) {
      j++;
      fc_assert(j < 8);
    }
  }

  return j;
}
