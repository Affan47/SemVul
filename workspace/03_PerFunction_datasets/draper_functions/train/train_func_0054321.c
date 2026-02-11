visibleTabs(void)
{
  int numVisible=0;
  if (orientation()==Horizontal)
   {
     int totalSpace=availableHeightForTabs();
     if (totalSpace>=totalTabHeight()) numVisible=numManaged();
     else
      {
	MSNodeItem *hp=childListHead();
	MSNodeItem *np=hp;
	NotebookEntry *entry;
	MSBoolean foundFirstEntry=MSFalse;
	while ((np=np->next())!=hp)
	 {
	   entry=(NotebookEntry *)np->data();
	   if (foundFirstEntry==MSTrue||entry==firstEntry())
	    {
	      foundFirstEntry=MSTrue;
	      if (entry->managed()==MSTrue)
	       {
		 if (entry->tab()->height()<=totalSpace)
		  {
		    int used=entry->tab()->height()+tabSpacing();
		    totalSpace-=used;
		    numVisible++;
		  }
		 else break;
	       }
	    }
	 }
      }
   }
  else
   {
     int totalSpace=availableWidthForTabs();
     if (totalSpace>=totalTabWidth()) numVisible=numManaged();
     else
      {
	MSNodeItem *hp=childListHead();
	MSNodeItem *np=hp;
	NotebookEntry *entry;
	MSBoolean foundFirstEntry=MSFalse;
	while ((np=np->next())!=hp)
	 {
	   entry=(NotebookEntry *)np->data();
	   if (foundFirstEntry==MSTrue||entry==firstEntry())
	    {
	      foundFirstEntry=MSTrue;
	      if (entry->managed()==MSTrue)
	       {
		 if (entry->tab()->width()<=totalSpace)
		  {
		    int used=entry->tab()->width()+tabSpacing();
		    totalSpace-=used;
		    numVisible++;
		  }
		 else break;
	       }
	    }
	 }
      }
   }
  return numVisible;
}
