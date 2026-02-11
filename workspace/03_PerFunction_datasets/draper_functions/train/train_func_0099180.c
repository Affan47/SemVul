getEntry(const char *title_) const
{
  MSNodeItem *hp=(MSNodeItem *)childListHead();
  MSNodeItem *np=hp;
  NotebookEntry *entry;
  MSString title(title_);
  while ((np=np->next())!=hp)
   {
     entry=(NotebookEntry *) np->data();
     if (entry->title()==MSStringVector(title)) return entry;
   }
  return 0;
}
