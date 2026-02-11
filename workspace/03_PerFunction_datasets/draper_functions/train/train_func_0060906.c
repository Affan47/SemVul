ParseContentType(SignalingProtocol protocol,
                      const buzz::XmlElement* action_elem,
                      std::string* content_type,
                      ParseError* error) {
  const buzz::XmlElement* content_elem;
  if (protocol == PROTOCOL_GINGLE) {
    if (!ParseContentType(action_elem, content_type, &content_elem, error))
      return false;


    if (*content_type == NS_GINGLE_AUDIO ||
        *content_type == NS_GINGLE_VIDEO)
      *content_type = NS_JINGLE_RTP;
  } else {
    const buzz::XmlElement* pair_elem
        = action_elem->FirstNamed(QN_JINGLE_CONTENT);
    if (pair_elem == NULL)
      return BadParse("No contents found", error);

    if (!ParseContentType(pair_elem, content_type, &content_elem, error))
      return false;


    for (; pair_elem != NULL;
         pair_elem = pair_elem->NextNamed(QN_JINGLE_CONTENT)) {
      std::string content_type2;
      if (!ParseContentType(pair_elem, &content_type2, &content_elem, error))
        return false;

      if (content_type2 != *content_type)
        return BadParse("More than one content type found", error);
    }
  }

  return true;
}
