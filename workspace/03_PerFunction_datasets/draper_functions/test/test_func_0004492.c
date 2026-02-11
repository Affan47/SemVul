earliestLogicallyAdjacentTextNode(const TextImpl* t)
{
    const NodeImpl* n = t;
    while ((n = n->previousSibling())) {
        unsigned short type = n->nodeType();
        if (type == Node::TEXT_NODE || type == Node::CDATA_SECTION_NODE) {
            t = static_cast<const TextImpl*>(n);
            continue;
        }


        assert(type != Node::ENTITY_REFERENCE_NODE || !n->hasChildNodes());
        break;
    }
    return t;
}
