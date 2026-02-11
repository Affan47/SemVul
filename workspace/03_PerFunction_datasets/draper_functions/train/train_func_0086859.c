message(MessageEvent *event)
{
  noteMessage(event->message());
  delete event;
}
