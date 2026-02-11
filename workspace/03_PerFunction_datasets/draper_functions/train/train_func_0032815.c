setOffset(int _offset)
{
  if (d->offset != _offset) {
    d->offset = _offset;
    update(contentsRect());
  }
}
