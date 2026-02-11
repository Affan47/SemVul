takeItem(Q3ListViewItem *item)
{
  if(item && item == d->editor->currentItem())
    d->editor->terminate();

  Q3ListView::takeItem(item);
}
