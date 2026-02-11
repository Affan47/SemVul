doNothing(Event *event)
{
  if (noOutput()) {
    delete event;
    return 1;
  }
  else
    return 0;
}
