addColumn(const QString& label, int width)
{
  int result = Q3ListView::addColumn(label, width);
  if (d->fullWidth) {
    header()->setStretchEnabled(false, columns()-2);
    header()->setStretchEnabled(true, columns()-1);
  }
  return result;
}
