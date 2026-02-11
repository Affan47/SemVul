addNewItems(const KUrl& directoryUrl, const KFileItemList& items)
{


  KFileItemList::const_iterator kit = items.begin();
  const KFileItemList::const_iterator kend = items.end();
  for ( ; kit != kend; ++kit )
    addNewItem(directoryUrl, *kit);
}
