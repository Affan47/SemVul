partsSelected(const TracePartList& l)
{
  if (_parentView)
      _parentView->partsSelected(this, l);
  else
      if (_topLevel) _topLevel->activePartsChangedSlot(l);
}
