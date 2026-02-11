returnKey(void)
{
  if (columnHasOptions(selectedColumn())==MSTrue)
    {
      showOptions(selectedRow(),selectedColumn());
    }
  else MSArrayView::returnKey();
}
