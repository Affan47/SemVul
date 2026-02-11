IsItemIndexVisible(List *list,int n)
{
  Item *temp;
  int i;

  for(i=0,temp=list->head;temp!=NULL && i<n;i++,temp=temp->next);
  if (temp == NULL) return 0;
  if (IsItemVisible(temp))
    return 1;
  else
    return 0;
}
