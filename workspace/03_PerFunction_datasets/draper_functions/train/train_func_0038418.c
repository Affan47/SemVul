selectedItems(bool includeHiddenItems) const
{
  QList<Q3ListViewItem *> list;


  switch(selectionMode())
  {
  case NoSelection:
      break;
  case Single:
      if(selectedItem() && (includeHiddenItems || selectedItem()->isVisible()))
          list.append(selectedItem());
      break;
  default:
  {
      int flags = Q3ListViewItemIterator::Selected;
      if (!includeHiddenItems)
      {
        flags |= Q3ListViewItemIterator::Visible;
      }

      Q3ListViewItemIterator it(const_cast<K3ListView *>(this), flags);

      for(; it.current(); ++it)
          list.append(it.current());

      break;
  }
  }

  return list;
}
