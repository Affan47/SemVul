show(void)
{
  if (mapped()==MSFalse)
   {
     MSNodeItem *hp=childListHead();
     MSNodeItem *np=hp;
     while ((np=np->next())!=hp)
      {
	NotebookEntry *entry=(NotebookEntry *)np->data();
	if (entry->widget()!=0)
	 {
	   entry->widget()->show();
	 }
	if (entry!=currentEntry()) entry->widget()->unmap();
      }
     map();
   }
}
