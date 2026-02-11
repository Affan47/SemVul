externalDataEntity(ExternalDataEntityEvent *event)
{
  currentLocation_ = event->location();
  outputLocation(event->location());
  flushData();
  if (!outputEntity_ && !markEntity(event->entity()))
    defineExternalDataEntity(event->entity());
  currentLocation_.clear();
  os() << referenceEntityCode << event->entity()->name() << nl;
  delete event;
}
