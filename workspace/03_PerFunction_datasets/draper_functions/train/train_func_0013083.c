UpdateItemGSFRFlags(List *list, ConfigWinPacket *cfgpacket)
{
  Item *temp;
  for(temp=list->head;temp!=NULL && cfgpacket->w!=temp->id;temp=temp->next);
  if (temp==NULL) return -1;
  temp->flags = cfgpacket->flags;
  return temp->count;
}
