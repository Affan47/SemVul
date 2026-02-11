max_freecells(Stack *excl1, Stack *excl2)
{
  int num, empty, i;
  empty = 0;
  num = 1;
  for (i=0; i<4; i++)
    if (stack_count_cards(freecells[i]) == 0)
      num++;
  for (i=0; i<8; i++)
    if (stack_count_cards(maincells[i]) == 0
	&& maincells[i] != excl1
	&& maincells[i] != excl2)
      num *= 2;
  return num;
}
