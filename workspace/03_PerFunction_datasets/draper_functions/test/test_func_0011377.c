nodeMatches(NodeImpl *testNode, bool& ) const
{
    if (testNode->nodeType() != Node::ELEMENT_NODE)
        return false;

    if (m_namespaceAware) {
        return (m_namespace.id() == anyNamespace || m_namespace.id() == namespacePart(testNode->id())) &&
            (m_localName.id() == anyLocalName || m_localName.id() == localNamePart(testNode->id()));
    } else {
        return (m_localName.id() == anyLocalName) || (m_localName.id() == localNamePart(testNode->id()) &&
            m_prefix == static_cast<ElementImpl*>(testNode)->prefixName());
    }
}
