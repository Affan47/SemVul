GetDeskNumber(List *list, int n, long *Desk)
{
  Item *temp;

  for (temp=list->head;temp && temp->count!=n;temp=temp->next);
  if (temp==NULL) return 0;
  *Desk=temp->Desk;
  return 1;
}
