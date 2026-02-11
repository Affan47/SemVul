calcLength(NodeImpl *start) const
{
    if (type != TABLE_ROWS)
        return DynamicNodeListImpl::calcLength(start);

    unsigned length = 0;
    const HTMLTableElementImpl* table = static_cast<const HTMLTableElementImpl*>(m_refNode);
    for (NodeImpl* kid = table->firstChild(); kid; kid = kid->nextSibling()) {
        HTMLCollectionImpl rows(kid, TSECTION_ROWS);
        length += rows.length();
    }
    return length;
}
