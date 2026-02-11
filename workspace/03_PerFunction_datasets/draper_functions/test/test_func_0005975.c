lastItem() const
{
  Q3ListViewItem* last = lastChild();

  for (Q3ListViewItemIterator it (last); it.current(); ++it)
    last = it.current();

  return last;
}
