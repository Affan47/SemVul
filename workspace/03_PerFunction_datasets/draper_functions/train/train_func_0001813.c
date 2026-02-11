IsWritable(SignalingProtocol protocol,
                const ContentInfo& content,
                const ContentParserMap& parsers) {
  ContentParser* parser = GetContentParser(parsers, content.type);
  if (parser == NULL) {
    return false;
  }

  return parser->IsWritable(protocol, content.description);
}
