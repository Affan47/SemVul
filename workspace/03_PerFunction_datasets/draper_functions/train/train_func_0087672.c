disableAutoSelection()
{
  if ( d->disableAutoSelection )
    return;

  d->disableAutoSelection = true;
  d->autoSelect.stop();
  d->autoSelectDelay = -1;
}
