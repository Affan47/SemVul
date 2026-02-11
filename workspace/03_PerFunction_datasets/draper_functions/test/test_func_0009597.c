tag_list (int *list, int len)
{
  int i;

  for (i = 0; i < len; i++)
    field[list[i]].tag = 1;
}
