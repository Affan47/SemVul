markedSectionStart(const MarkedSectionStartEvent &event)
{
  if (outputState_ == pendingRe) {
    numCharRef(RE);
    outputState_ = other;
  }
  os() << "<![";
  for (size_t i = 0; i < event.nParams; i++)
    switch (event.params[i].type) {
    case MarkedSectionStartEvent::Param::temp:
      os() << " TEMP";
      break;
    case MarkedSectionStartEvent::Param::include:
      os() << " INCLUDE";
      break;
    case MarkedSectionStartEvent::Param::rcdata:
      os() << " RCDATA";
      break;
    case MarkedSectionStartEvent::Param::cdata:
      os() << " CDATA";
      break;
    case MarkedSectionStartEvent::Param::ignore:
      os() << " IGNORE";
      break;
    case MarkedSectionStartEvent::Param::entityRef:
      os() << " %" << event.params[i].entityName << ";";
      break;
    }
  switch (event.status) {
  case MarkedSectionStartEvent::cdata:
    parseMode_ = cdataMode;
    break;
  case MarkedSectionStartEvent::rcdata:
    parseMode_ = rcdataMode;
    break;
  default:
    break;
  }
  os() << " [";
}
