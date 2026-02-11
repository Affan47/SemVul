ParseJingleTransportInfo(const buzz::XmlElement* trans_elem,
                              const ContentInfo& content,
                              const TransportParserMap& trans_parsers,
                              TransportInfos* tinfos,
                              ParseError* error) {
  std::string transport_type = trans_elem->Name().Namespace();
  TransportInfo tinfo(content.name, transport_type, Candidates());
  if (!ParseCandidates(PROTOCOL_JINGLE, trans_elem,
                       trans_parsers, transport_type,
                       &tinfo.candidates, error))
    return false;

  tinfos->push_back(tinfo);
  return true;
}
