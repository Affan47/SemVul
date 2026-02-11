entityDefaulted(EntityDefaultedEvent *event)
{
  grove_->addDefaultedEntity(event->entityPointer());
  delete event;
}
