line(int row) const
{
  int n = d->history.size() - row - 1;
  if (d->historyOverlay.contains(n))
    return d->historyOverlay[n];
  else if (n >= 0  && n < d->history.size())
    return d->history[n];
  return QString();
}
