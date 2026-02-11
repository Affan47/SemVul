setFieldStop(int f, const QString& stop)
{
  if (((int)_attr.size() < f+1) &&
      (stop == defaultFieldStop(f))) return;
  if (resizeAttr(f+1)) {
    _attr[f].stop = stop;
    redraw();
  }
}
