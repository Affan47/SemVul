invalidate()
{
  if (_dirty) return;
  _dirty = true;

  if (_dep)
    _dep->invalidate();
}
