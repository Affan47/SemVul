data(DataEvent *event)
{
  outputLocation(event->location());
  startData();
  outputString(event->data(), event->dataLength());
  delete event;
}
