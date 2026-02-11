WriteSessionTerminate(SignalingProtocol protocol,
                           const SessionTerminate& term,
                           XmlElements* elems) {
  if (protocol == PROTOCOL_GINGLE) {
    elems->push_back(new buzz::XmlElement(buzz::QName(NS_GINGLE, term.reason)));
  } else {
    if (!term.reason.empty()) {
      buzz::XmlElement* reason_elem = new buzz::XmlElement(QN_JINGLE_REASON);
      reason_elem->AddElement(new buzz::XmlElement(
          buzz::QName(NS_JINGLE, term.reason)));
      elems->push_back(reason_elem);
    }
  }
}
