isImmutable(const QString &name) const
{
  KConfigSkeletonItem *item = findItem(name);
  return !item || item->isImmutable();
}
