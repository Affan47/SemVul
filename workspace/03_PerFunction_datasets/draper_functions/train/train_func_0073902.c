send(ParserState &parser)
{
  parser.Messenger::setNextLocation(location_);
  parser.message(*message_, StringMessageArg(id_));
}
