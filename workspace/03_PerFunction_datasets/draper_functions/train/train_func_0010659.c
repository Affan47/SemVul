PrintList(List *list)
{
Item *temp;
  ConsoleMessage("List of Items:\n");
  ConsoleMessage("   %10s %-15s %-15s %-15s %-15s Flgs\n","ID","Name","I-Name",
    "R-Name","R-Class");
  ConsoleMessage("   ---------- --------------- --------------- --------------- --------------- ----\n");
  for(temp=list->head;temp!=NULL;temp=temp->next) {
    ConsoleMessage("   %10ld %-15.15s %4d\n",temp->id,
      (temp->name==NULL) ? "<null>" : temp->name,
       temp->flags);
  }
}
