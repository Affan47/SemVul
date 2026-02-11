get_aa_value(int str)
{
  int stones[MAX_BOARD * MAX_BOARD];
  int k;
  int num_stones = findstones(str, MAX_BOARD * MAX_BOARD, stones);
  int value = 0;

  for (k = 0; k < num_stones; k++)
    value += aa_values[stones[k]];

  return value;
}
