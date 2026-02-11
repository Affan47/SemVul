selectionClear(const XEvent *)
{
  if (server()->primarySelectionOwner()==this) server()->primarySelectionOwner(0);
  clearSelection();
}
