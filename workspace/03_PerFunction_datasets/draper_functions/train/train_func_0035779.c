childMap(MSWidget *widget_)
{
  if (widget_!=this)
   {
     MSLayoutEntry *entry=findMappedEntry(widget_);
     if (entry==0)
      {
	entry=getEntry(widget_);
	entry->mapped(MSTrue);
	insertMappedEntry(entry);
        adjustSize();
      }
   }
}
