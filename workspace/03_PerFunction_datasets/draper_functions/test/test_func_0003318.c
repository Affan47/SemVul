updateBackground(unsigned long oldbg_)
{
  MSArrayView::updateBackground(oldbg_);
  unsigned i,n=numColumns();
  for (i=0;i<n;i++) ((AplusTableColumn *)tableColumn(i))->setBg(background());
  n=hiddenColumnList()->count();
  for (i=n-1;i<n;i--)
  {
     MSTableColumn *tc=(MSTableColumn *)hiddenColumnList()->array(i);
     ((AplusTableColumn*)tc)->setBg(background());
  }
}
