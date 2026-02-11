useDefaults(bool b)
{
  if (b == d->mUseDefaults)
    return d->mUseDefaults;

  d->mUseDefaults = b;
  KConfigSkeletonItem::List::ConstIterator it;
  for( it = d->mItems.constBegin(); it != d->mItems.constEnd(); ++it )
  {
    (*it)->swapDefault();
  }
  usrUseDefaults(b);
  return !d->mUseDefaults;
}
