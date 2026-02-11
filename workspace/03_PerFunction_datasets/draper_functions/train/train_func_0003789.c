matchAttribute(const StringC &name,
					const StringC &value,
					const NodePtr &nd,
					MatchContext &context)
{
  NamedNodeListPtr atts;
  if (nd->getAttributes(atts) != accessOK)
    return 0;
  NodePtr att;
  if (atts->namedNode(GroveString(name.data(), name.size()), att) != accessOK)
    return 0;
  bool implied;
  if (att->getImplied(implied) == accessOK && implied)
    return 0;
  GroveString tokens;
  if (att->tokens(tokens) == accessOK) {
    if (tokens.size() != value.size())
      return 0;
    NodePtr node;
    NamedNodeListPtr normalizer;
    if (att->firstChild(node) != accessOK
        || node->getEntity(node) != accessOK
	|| node->getGroveRoot(node) != accessOK
	|| node->getEntities(normalizer) != accessOK)
      normalizer = atts;
    StringC tem(value);
    tem.resize(normalizer->normalize(&tem[0], tem.size()));
    if (tokens != GroveString(tem.data(), tem.size()))
      return 0;
  }
  else {
    NodePtr tem;
    StringC s;
    if (att->firstChild(tem) == accessOK) {
      do {
  	GroveString chunk;
	if (tem->charChunk(context, chunk) == accessOK)
	  s.append(chunk.data(), chunk.size());
	} while (tem.assignNextChunkSibling() == accessOK);
    }
    if (s != value)
      return 0;
  }
  return 1;
}
