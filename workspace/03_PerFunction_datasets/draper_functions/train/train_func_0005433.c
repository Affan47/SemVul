nonSgmlChar(NonSgmlCharEvent *event)
{
  if (outputNonSgml_) {
    outputLocation(event->location());
    startData();
    os() << "\\%" << (unsigned long)event->character() << ';';
  }
  delete event;
}
