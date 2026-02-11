resetAutoSelection()
{
  if ( !d->disableAutoSelection )
    return;

  d->disableAutoSelection = false;
  d->autoSelectDelay = KGlobalSettings::autoSelectDelay();
}
