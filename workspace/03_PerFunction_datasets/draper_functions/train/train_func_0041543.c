addRecentFile(QString fname)
{
  d->recentFiles.removeAll(fname);
  d->recentFiles.prepend(fname);
  while(d->recentFiles.size() > 8)
    d->recentFiles.removeLast();
}
