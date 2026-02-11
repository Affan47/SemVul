snew(int num)
{
  STATEQ *new;
  int i;

  new = (STATEQ *)malloc(sizeof(STATEQ));
  new->s = (char *)malloc(sizeof(char)*num);
  new->len = num;
  new->ac = NULL;
  new->next = NULL;
  for(i=0;i<num;i++) new->s[i] = 0;
  new->checked = 0;
  new->start = 0;
  new->end = 0;
  return new;
}
