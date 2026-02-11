readConfig()
{

  d->mConfig->reparseConfiguration();
  KConfigSkeletonItem::List::ConstIterator it;
  for( it = d->mItems.constBegin(); it != d->mItems.constEnd(); ++it )
  {
    (*it)->readConfig( d->mConfig.data() );
  }
  usrReadConfig();
}
