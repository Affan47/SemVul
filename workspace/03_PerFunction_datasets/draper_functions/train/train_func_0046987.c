pi(PiEvent *event)
{
  flushLine(dataLine);
  os() << "[?";
  size_t dataLength = event->dataLength();
  if (dataLength > 0) {
    const Char *data = event->data();
    if (dataLength >= 4
	&& memcmp(data,
		  rastParseSubdocYesString_.data(),
		  4*sizeof(Char)) == 0
	&& !interpretRastPi(data, dataLength, event->location())) {
      setNextLocation(event->location());
      Messenger::message(RastEventHandlerMessages::invalidRastPiError);
    }
    os() << nl;
    lines(dataLine, event->data(), dataLength);
    flushLine(dataLine);
  }
  os() << ']' << nl;
  delete event;
}
