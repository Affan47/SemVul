nodeAttributeString(const NodePtr &node, const Char *s, size_t n,
			 const SdataMapper &mapper, StringC &value)
{
  NamedNodeListPtr atts;
  if (node->getAttributes(atts) != accessOK)
    return 0;
  NodePtr att;
  if (atts->namedNode(GroveString(s, n), att) != accessOK)
    return 0;
  bool implied;
  if (att->getImplied(implied) == accessOK && implied)
    return 0;
  GroveString tokens;
  if (att->tokens(tokens) == accessOK) {
    value.assign(tokens.data(), tokens.size());
    return 1;
  }
  NodePtr tem;
  value.resize(0);
  if (att->firstChild(tem) == accessOK) {
    do {
      GroveString chunk;
      if (tem->charChunk(mapper, chunk) == accessOK)
	value.append(chunk.data(), chunk.size());
    } while (tem.assignNextChunkSibling() == accessOK);
  }
  return 1;
}
