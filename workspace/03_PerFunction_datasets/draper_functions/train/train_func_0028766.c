resetFirstEntry(void)
{
  if (currentEntry()!=0)
   {
     if (firstEntry()==0) firstEntry(firstItem());
     MSWidgetVector managedVector=managedChildren();
     int first=managedVector.indexOf((unsigned long)firstEntry()->widget());
     int current=managedVector.indexOf((unsigned long)currentEntry()->widget());
     if (current<first)
      {
	firstEntry(currentEntry());
      }
     else
      {
	int numShown=visibleTabs();
	if (current>=first+numShown)
	 {
	   lastEntry(currentEntry());
	 }
      }
   }
  else if (numManaged()==0)
   {
     firstEntry(0);
   }
}
