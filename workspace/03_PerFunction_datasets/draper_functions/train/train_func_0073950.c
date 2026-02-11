nonSgmlChar(NonSgmlCharEvent *event)
{
  flushLine(dataLine);
  os() <<'#' << (unsigned long)event->character() << nl;
  delete event;
}
