elementNumberAfter(const NodePtr &node, const StringC &gi,
					      const StringC &resetGi)
{
  NodePtr start;
  NodePtr lastMatch;
  unsigned long resetCount = 0;
  unsigned long count = 0;
  ElementEntry *entry = elementNumbers_.lookup(resetGi);
  if (entry) {
    unsigned long nodeIndex, entryIndex;
    bool useSubnode = 1;
    node->elementIndex(nodeIndex);
    unsigned long nodeGroveIndex = node->groveIndex();
    if (entry->node) {
      if (*entry->node == *node)
	return 0;
      entry->node->elementIndex(entryIndex);
      if (entryIndex < nodeIndex && entry->node->groveIndex() == nodeGroveIndex) {
	start = lastMatch = entry->node;
	advance(start);
	resetCount = entry->num;
      }
      else
	useSubnode = 0;
    }
    if (entry->subNode && useSubnode) {
      GroveString tem;
      if (entry->subNode->getGi(tem) == accessOK
	  && tem == GroveString(gi.data(), gi.size())) {
	if (*entry->subNode == *node)
	  return entry->subNum;
	entry->subNode->elementIndex(entryIndex);
	if (entryIndex < nodeIndex && entry->subNode->groveIndex() == nodeGroveIndex) {
	  start = entry->subNode;
	  advance(start);
	  count = entry->subNum;
	}
      }
    }
  }
  else
    elementNumbers_.insert(entry = new ElementEntry(resetGi));
  if (!start) {
    node->getGroveRoot(start);
    start->getDocumentElement(start);
  }
  for (;;) {
    GroveString tem;
    if (start->getGi(tem) == accessOK) {
      if (tem == GroveString(resetGi.data(), resetGi.size())) {
	lastMatch = start;
	resetCount++;
	count = 0;
      }
      else if (tem == GroveString(gi.data(), gi.size()))
	count++;
    }
    if (*start == *node)
      break;
    advance(start);
  }
  entry->node = lastMatch;
  entry->num = resetCount;
  entry->subNode = node;
  entry->subNum = count;
  return count;
}
